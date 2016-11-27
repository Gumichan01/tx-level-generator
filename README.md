# Target Xplosion Level Generator #

## Introduction ##

This program generates a level file that contains information about enemies
(type, health points, attack points,...) according to a text file.

## How to use the generator ##

In a console interface, use the program like this:

On Linux:

    ./tx-lvl-gen [text_file] [file_to_write_data]

On Windows:

    tx-lvl-gen.exe [text_file] [file_to_write_data]


### The text file ###

This is an example of a text file you have to write:

    # A line comment (it will be ignored)
    4
    101 20 10 5 4000 100 47 47
    102 20 10 5 4500 200 47 47
    102 20 10 5 4500 300 47 47
    # Another comment (ignored)
    101 20 10 5 5000 100 47 47


First of all, the file has the number of lines that represents the number of
enemy data.
If you do not put the number, the program may fail or generate a bad file.

After that, you have several lines. Each line represents an enemy data.
The syntax of each data is:

    [type]_[health]_[attack]_[defense]_[timeToAppear]_[Yposition]_[width]_[height]

NB : each '\_' is a space.
The type is the ID of the enemy. You can take a look on the wiki to get information about that.
The X position is automatically set by the game. You do not need to handle it.
The *timeToAppear* value refers to the moment an enemy must go in the game.

**If at least one field is mising or if you put too much fields, the program will fail.**

### The generated file ###

In Target Xplosion, it is better to give the *.targetx* extension to the generated file.
However, the program does not check if the destination file has this extension.
Actually it will just check if the file exists in the directory and if it is valid.

The syntax of a level file name is:

    XX.targetx

XX is a number between 00 and 99.

The file contains a tag (*0xCF3A1* or *848801*) followed by the number of lines
and data, and has the same tag at the end. This tag is necessary to check
if the file will be used for the game.
