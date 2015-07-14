# Makefile for CS251 Program 2
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
APP=dequer

# Our object files
OFILES=Dequer.o Deque.o Main.o

# Changes in these files should trigger an entire rebuild
ALLDEP=Makefile

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

Main.o:	Dequer.h

Dequer.o: Deque.h


