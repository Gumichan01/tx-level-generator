# Target Xplosion Level Generator #


## Introduction ##

This program generates a level file that contains information about enemies  
(type, health points, attack points,...) according to a text file.


## How to use the generator ##


In a console interface, use the program like this:

On Linux:  

    ./TX-level-generator [text\_file] [file\_to\_write\_data]  

On Windows:

    TX-level-generator.exe [text\_file] [file\_to\_write\_data]  


### The text file ###

This is an example of a text file you have to write:  

    2 
    101 20 10 5 4000 100 47 47 
    101 20 10 5 4500 200 47 47 

**Do not forget to add the space before the next line.**  

First of all, the file has the number of lines that represent the number of enemy data.  
If you do not put the number, the program may fail or generate a bad file.

After that, you have several lines. Each line represents an enemy data.  
The syntax of each data is:  

    [type]\_[health]\_[attack]\_[defense]\_[timeToAppear]\_[Yposition]\_[width]\_[height]\_

NB : each '\_' is a space.  
The type is an ID of the enemy. You can take a look on the wiki to get information about that.  
The X position is automatically set by the game. You do not need to handle it.  
The *timeToAppear* value refers to the moment an enemy must go in the game.  

**If at least one field is mising or if you put too much fields, the program will fail.**  


### The generated file ###

In Target Xpolosion, it is better to give the *.targetx* extension to the generated file.  
The program does not check if the destination file has this extension.  
Actually it will just check if the file exists in the directory.

The syntax of a level file is:

    XX.targetx

XX is a number between 00 and 99.

The file contains a tag (0xCF3A1 or 848801) followed by the number of objects  
and the data, and has the same tag at the end. This tag is necessary to check 
if the file will be used for the game.



