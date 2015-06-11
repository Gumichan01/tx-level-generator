
/*
*   TX Level Generator - The level generator for Target Xplosion
*	Copyright (C) 2015  Luxon Jean-Pierre
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
*	website : gumichan01.olympe.in
*	mail : luxon.jean.pierre@gmail.com
*/

/**
*	@file LevelGenerator.cpp
*	@brief The level generator implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <cstdio>
#include <cstdlib>

#include <new>
#include <fstream>
#include <sstream>

#include "LevelGenerator.hpp"
#include "EnemyData.hpp"


#define NB_FIELD 8


using namespace std;


namespace LevelGenerator
{


LevelData::LevelData(const char *filename)
{
    data = NULL;
    read(filename);
}


void LevelData::read(const char *filename)
{
    ifstream reader;
    string line, token;
    string delimiter = " ";
    stringstream valueStream;

    size_t pos;
    int field;
    int i = 0;
    size = 0;

    if(filename == NULL)
        return;

    reader.open(filename,ios::in);

    if(reader.is_open() == false)
    {
        cerr << "Cannot open " << filename << endl;
        return;
    }

    cout << "Reading file: " << filename << endl;

    if(getline(reader,line))
    {
        if((pos = line.find(delimiter)) != string::npos)
        {
            token = line.substr(0, pos);
            valueStream.clear();
            valueStream.str("");
            valueStream.str(token);
            valueStream >> size;
        }
    }

    cout << "Number of data to extract: " << size << endl;

    data = new (nothrow) EnemyData[size];

    if(data == NULL)
    {
        cerr << "Error while creating data; Invalid size: " << size << endl;
        reader.close();
        return;
    }

    while( i < size && getline(reader,line))
    {
        pos = 0;
        field = 0;

        while((pos = line.find(delimiter)) != string::npos)
        {
            token = line.substr(0, pos);

            valueStream.clear();
            valueStream.str("");
            valueStream.str(token);

            switch(field)
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

            line.erase(0, pos + delimiter.length());
            field++;
        }

        // End of line. Did we read the expected fields?
        if(field != NB_FIELD)
        {
            cerr << "Error: line #" << (i+2) << ": Expected " << NB_FIELD
                 << " fields; Got " << field <<" fields" << endl;
            delete [] data;
            data = NULL;
            reader.close();
            break;
        }
        else
        {
            cout << "Got Data "<<i<<" : \n" << data[i].type << " "
                 << data[i].hp << " " << data[i].att << " " << data[i].sh
                 << " " << data[i].time << " " << data[i].y << " " << data[i].w
                 << " " << data[i].h << endl;
        }

        i++;
    }

    if(i < size)
    {
        cout << "WARNING: Some data are missing, but the generation can be done" << endl;
        size = i;
    }

    reader.close();
}



bool LevelData::generateFile(const char *filename)
{
    FILE * writer;
    stringstream s;
    string str;
    const int tag = 0xCF3A1;

    if(filename == NULL)
    {
        cerr << "Invalid file name: NULL" << endl;
        return false;
    }

    if(data == NULL)
    {
        cerr << "No data available" << endl;
        return false;
    }

    if(size < 0)
    {
        cerr << "Invalid size" << endl;
        return false;
    }

    writer = fopen(filename,"wb");

    if(writer == NULL)
    {
        cerr << "Internal error : try again !" << endl;
        return false;
    }

    cout << "Writing into file: " << filename << endl;

    cout << "Writing tag" << endl;
    fwrite(&tag,sizeof(int),1,writer);

    cout << "Writing size" << endl;
    fwrite(&size,sizeof(int),1,writer);

    const int n = size;

    for(int i = 0; i < n; i++)
    {
        cout << "Writing data #" << (i+1) << endl;
        writeData(&data[i],writer);
    }

    cout << "Writing tag at the end of the file" << endl;

    fwrite(&tag,sizeof(int),1,writer);
    fclose(writer);

    return true;
}


void LevelData::writeData(const EnemyData *edata, FILE *writer)
{
    fwrite(&edata->type,sizeof(unsigned int),1,writer);
    fwrite(&edata->hp,sizeof(unsigned int),1,writer);
    fwrite(&edata->att,sizeof(unsigned int),1,writer);
    fwrite(&edata->sh,sizeof(unsigned int),1,writer);
    fwrite(&edata->time,sizeof(unsigned int),1,writer);
    fwrite(&edata->y,sizeof(unsigned int),1,writer);
    fwrite(&edata->w,sizeof(unsigned int),1,writer);
    fwrite(&edata->h,sizeof(unsigned int),1,writer);
}



LevelData::~LevelData()
{
    delete [] data;
}

};



