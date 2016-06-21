
#   TX Level Generator - The level generator for Target Xplosion
#	Copyright (C) 2016  Luxon Jean-Pierre

CC=g++
DIR=src/
EXEC=tx-lvl-gen

FLAGS=-Wall -O3 -std=c++0x

all : $(EXEC)

$(EXEC) : LevelGenerator.o main.o
	$(CC) -o $@ $^ $(FLAGS) -lstdc++

LevelGenerator.o : $(DIR)LevelGenerator.cpp $(DIR)LevelGenerator.hpp
	$(CC) -c -o $@ $< $(FLAGS)

main.o : $(DIR)main.cpp
	$(CC) -c -o $@ $< $(FLAGS)

clean :
	rm -f *.o

clear : clean
	rm -f $(EXEC)
