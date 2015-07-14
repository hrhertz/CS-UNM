# Makefile for CS251 Program 5

# Our application version
VERSION=1.0

# Compile-time flags
CFLAGS=-g -Wall -pedantic -c

# Link-time flags (don't need any..)
LFLAGS=

# Command for compilation
CPP=g++

# Command for linking
LINK=g++

# Our final program name
APP=TPL
# UNCOMMENT THE FOLLOWING LINE (REMOVE THE '#' FROM IT) TO BUILD 'TPLI' INSTEAD
#APP=TPLI

# Object files needed to build APP
OFILES=Main.o Parser.o Node.o

# Files for which changes should force everything to be remade:
ALLDEP=Makefile

all:	$(APP)

# Linking the main app
$(APP):	$(ALLDEP) $(OFILES)
	$(LINK) $(OFILES) -o $(APP)

# Compiling the source files
%.o:	%.C %.h $(ALLDEP)
	$(CPP) -c $(CFLAGS) $*.C -o $@ 

# cleaning
clean:
	rm -f *.o core *~ $(APP)*.tgz

distclean:	clean
	rm -f $(APP)

distrib:	distclean
	tar cvzf ../$(APP)-$(VERSION).tgz *

#######
# Other dependencies
Main.o:	Parser.h

Parser.o: Node.h

