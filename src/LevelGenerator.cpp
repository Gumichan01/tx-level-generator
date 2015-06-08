

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


#include <fstream>

#include "LevelGenerator.hpp"
#include "EnemyData.hpp"


using namespace std;


namespace LevelGenerator
{


LevelData::LevelData(const char *filename)
{
    cout << "Constructor" << endl;
    data = NULL;
    read(filename);
}


void LevelData::read(const char *filename)
{
    ifstream reader;
    string line, token;
    string delimiter = " ";
    size_t pos;

    if(filename == NULL)
        return;

    reader.open(filename,ios::in);
    cout << "READ" << endl;

    while(getline(reader,line))
    {
        pos = 0;

        while((pos = line.find(delimiter)) != string::npos)
        {
            token = line.substr(0, pos);
            cout << token << endl;
            line.erase(0, pos + delimiter.length());
        }
        cout << "END OF LINE" << endl;
    }
    //cout << "Last " << token << endl;
    reader.close();
}



LevelData::~LevelData()
{
    cout << "Destructor" << endl;
    delete [] data;
}

};



