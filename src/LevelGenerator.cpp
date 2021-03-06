
/*
*   TX Level Generator - The level generator for Target Xplosion
*	Copyright © 2018 Luxon Jean-Pierre
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*	Luxon Jean-Pierre (Gumichan01)
*	website: https://gumichan01.github.io/
*	mail: luxon.jean.pierre@gmail.com
*/

#include <cstdio>
#include <cstdlib>

#include <new>
#include <fstream>
#include <sstream>

#include "LevelGenerator.hpp"
#include "EnemyData.hpp"

#define NB_FIELD 8
#define COMMENT_LINE '#'
using namespace std;

namespace LevelGenerator
{

LevelData::LevelData( const char * filename )
{
    data = nullptr;
    read( filename );
}

// Read, extract, and store the data
void LevelData::read( const char * filename ) noexcept
{
    ifstream reader;
    string line, token;
    string delimiter = " ";
    stringstream valueStream;

    int field;
    size_t i = 0;
    size = 0;

    if ( filename == nullptr )
        return;

    reader.open( filename, ios::in );

    if ( reader.is_open() == false )
    {
        cerr << "Cannot open " << filename << "\n";
        return;
    }

    cout << "Reading file: " << filename << "\n";

    // Read a line and get the number of data
    while ( getline( reader, line ) )
    {
        if ( line[0] == COMMENT_LINE )
            continue;

        token = line.substr( 0 );
        valueStream.clear();
        valueStream.str( token );
        valueStream >> size;
        break;
    }

    cout << "Number of data to extract: " << size << "\n";

    // We have got the number of data to extract
    data = new ( nothrow ) EnemyData[size];

    if ( data == nullptr )
    {
        cerr << "Error while creating data; Invalid size: " << size << "\n";
        reader.close();
        return;
    }

    size_t pos;

    // Read the file line by line until the end of file
    // or we read the number of data.
    // Each line represent an enemy data
    while ( i < size && getline( reader, line ) )
    {
        if ( line.empty() || line[0] == COMMENT_LINE )
            continue;

        pos = 0;
        field = 0;

        // Gets the tokens of the line and fill in the enemy data structure
        while ( ( pos = line.find( delimiter ) ) != string::npos || !line.empty() )
        {
            valueStream.clear();

            if ( pos != string::npos )
                token = line.substr( 0, pos );
            else
                token = line;

            valueStream.str( token );

            switch ( field )
            {
            case 0 :
                valueStream >> data[i].type;
                break;

            case 1 :
                valueStream >> data[i].hp;
                break;

            case 2 :
                valueStream >> data[i].att;
                break;

            case 3 :
                valueStream >> data[i].sh;
                break;

            case 4 :
                valueStream >> data[i].time;
                break;

            case 5 :
                valueStream >> data[i].y;
                break;

            case 6 :
                valueStream >> data[i].w;
                break;

            case 7 :
                valueStream >> data[i].h;
                break;

            default :
                break;
            }

            if ( field < NB_FIELD - 1 )
                line.erase( 0, pos + delimiter.length() );
            else
                line.clear();

            field++;
        }

        // End of line. Did we read the expected fields?
        // If we read too much or not enough field, the file is not valid
        if ( field != NB_FIELD )
        {
            // Fail
            cerr << "Error: line #" << ( i + 2 ) << ": Expected " << NB_FIELD
                 << " fields; Got " << field << " fields\n";
            delete [] data;
            data = nullptr;
            reader.close();
            break;
        }
        else
        {
            cout << "Got Data " << i << " : \n" << data[i].type << " "
                 << data[i].hp << " " << data[i].att << " " << data[i].sh
                 << " " << data[i].time << " " << data[i].y << " " << data[i].w
                 << " " << data[i].h << "\n";
        }
        i++;
    }

    if ( i < size )
    {
        // The program read less data than expected
        // This is not a pity because the program can
        // write the given data into the generated file
        cout << "WARNING: Some data are missing, but the generation can be done\n";
        size = i;
    }

    reader.close();
}


// Generate the level file
bool LevelData::generateFile( const char * filename ) noexcept
{
    FILE * writer;
    const int tag = 0xCF3A1;    // This tag is necessary to check the file

    if ( filename == nullptr )
    {
        cerr << "Invalid file name: nullptr\n";
        return false;
    }

    if ( data == nullptr )
    {
        cerr << "No data available\n";
        return false;
    }

    writer = std::fopen( filename, "wb" );

    if ( writer == nullptr )
    {
        cerr << "Internal error : try again !\n";
        return false;
    }

    cout << "Writing into file: " << filename << "\n";

    cout << "Writing tag\n";
    std::fwrite( &tag, sizeof( int ), 1, writer );

    cout << "Writing size\n";
    std::fwrite( &size, sizeof( int ), 1, writer );

    const size_t N = size;

    // Write the data into the level file
    for ( size_t i = 0; i < N; i++ )
    {
        cout << "Writing data #" << ( i + 1 ) << "\n";
        writeData( &data[i], writer );
    }

    // The tag is written again to be sure the file is still valid
    cout << "Writing tag at the end of the file\n";

    std::fwrite( &tag, sizeof( int ), 1, writer );
    std::fclose( writer );

    return true;
}

// There is no test to verify if the data was correcly written
void LevelData::writeData( const EnemyData * edata, FILE * writer ) noexcept
{
    std::fwrite( &edata->type, sizeof( unsigned int ), 1, writer );
    std::fwrite( &edata->hp, sizeof( unsigned int ), 1, writer );
    std::fwrite( &edata->att, sizeof( unsigned int ), 1, writer );
    std::fwrite( &edata->sh, sizeof( unsigned int ), 1, writer );
    std::fwrite( &edata->time, sizeof( unsigned int ), 1, writer );
    std::fwrite( &edata->y, sizeof( unsigned int ), 1, writer );
    std::fwrite( &edata->w, sizeof( unsigned int ), 1, writer );
    std::fwrite( &edata->h, sizeof( unsigned int ), 1, writer );
}

LevelData::~LevelData()
{
    delete [] data;
}

}
