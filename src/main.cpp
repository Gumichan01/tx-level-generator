
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

#include <iostream>
#include "LevelGenerator.hpp"

using namespace std;
using namespace LevelGenerator;


int main(int argc, char **argv)
{
    if(argc < 3)
    {
        cerr << "Usage: TX-level-generator " << "<text_file> "
             << "<file_to_write_data>" << endl;
        return -1;
    }

    cout << "TX Level Generator - The level generator for Target Xplosion\n"
         << "Copyright (C) 2015 Luxon Jean-Pierre\n" << endl;

    LevelData data(argv[1]);

    if(data.generateFile(argv[2]) == false)
    {
        cerr << "Cannot generate the following file: " << argv[2] << endl;
        return -2;
    }
    else
        cout << "The generation of '" << argv[2] << "' was done with success" << endl;

    return 0;
}
