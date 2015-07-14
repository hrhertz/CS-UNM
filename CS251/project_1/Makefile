# Makefile for CS251 Program 1
# WARNING! WARNING! WARNING!
# DO >>NOT<< COPY THIS FILE from your browser window USING CUT-AND-PASTE!
#   IF YOU DO, THIS FILE WILL NOT WORK!
# See http://www.cs.unm.edu/~ackley/cs251/projects/makefile-warnings.txt
#   for more information!

# Compile-time flags
CFLAGS=-g -Wall -pedantic -c

# Command for compilation
CPP=g++

# Command for linking
LINK=g++

# Our application name
APP=blocks

# Our object files
OFILES=Board.o Block.o Main.o

# Default target
all:	$(APP)

# Linking the main app
$(APP):	$(ALLDEP) $(OFILES)
	$(LINK) $(OFILES) -o $(APP)

# Compiling the source files
%.o:	%.C %.h $(ALLDEP)
	$(CPP) -c $(CFLAGS) $*.C -o $@ 

# Alternate target: cleaning
clean:
	rm -f *.o core *~

#######
# Other dependencies

Main.o:	Board.h

Board.o: Block.h


