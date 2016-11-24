#ifndef LEVELGENERATOR_HPP_INCLUDED
#define LEVELGENERATOR_HPP_INCLUDED


/*
*   TX Level Generator - The level generator for Target Xplosion
*	Copyright (C) 2016  Luxon Jean-Pierre
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
*	website : https://gumichan01.github.io/
*	mail : luxon.jean.pierre@gmail.com
*/

/**
*	@file LevelGenerator.hpp
*	@brief The level generator library
*	@author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <iostream>

using namespace std;
struct EnemyData;

namespace LevelGenerator
{

class LevelData
{

    int size;           /**< The number of enemies in the generated level */
    EnemyData *data;    /**< Information about each enemy */

    void read(const char *filename);
    void writeData(const EnemyData *edata,FILE *writer);

public:

    explicit LevelData(const char *filename);
    bool generateFile(const char *filename);

    ~LevelData();
};

};

#endif // LEVELGENERATOR_HPP_INCLUDED
