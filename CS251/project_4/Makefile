# Makefile for CS251 Program 4
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

# Our application names
CHARAPP=CharDequer
CHAROFILES=CharMain.o

LABELAPP=LabelDequer
LABELOFILES=LabelMain.o Label.o

# Changes in these files should trigger an entire rebuild
ALLDEP=Makefile

# Default target
all:	$(CHARAPP) $(LABELAPP)

# Linking the main apps
$(CHARAPP):	$(ALLDEP) $(CHAROFILES)
	$(LINK) $(CHAROFILES) -o $(CHARAPP)

$(LABELAPP):	$(ALLDEP) $(LABELOFILES)
	$(LINK) $(LABELOFILES) -o $(LABELAPP)

# Compiling the source files
%.o:	%.C %.h $(ALLDEP)
	$(CPP) -c $(CFLAGS) $*.C -o $@ 

# Alternate target: cleaning
clean:
	rm -f *.o core *~ 

#######
# Other dependencies

CharMain.o:	Dequer.h Dequer.template

LabelMain.o:	Dequer.h Dequer.template Label.h

Dequer.o:	Deque.h


