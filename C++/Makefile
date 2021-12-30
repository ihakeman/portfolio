# A simple Makefile
# Assumes the following directory hierarchy:
# Folder
# 	src
#       include

#this Makefile goes in the src directory

#the executable will be called database.out
EXECUTABLE := database

# the source files to be built
SOURCES := *.cpp


INCLUDES := -I ../include
EXT := out #file extension
CC := g++ #compiler

all:
	$(CC) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE).$(EXT)

realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;
	find . -type f -name "*.out" -exec rm '{}' \;
	find . -type f -name "*.gch" -exec rm '{}' \;

# this line required by make - don't delete
