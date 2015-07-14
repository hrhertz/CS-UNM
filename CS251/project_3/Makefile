# Makefile for CS251 Program 3
# WARNING! WARNING! WARNING!
# DO >>NOT<< COPY THIS FILE from your browser window USING CUT-AND-PASTE!
#   IF YOU DO, THIS FILE WILL NOT WORK!
# See http://www.cs.unm.edu/~ackley/cs251/projects/makefile-warnings.txt
#   for more information!

# Our application version (increment this every time you do 'make distrib')
VERSION=0.9

# Compile-time flags
CFLAGS+=-g -Wall -pedantic -c -Werror

# Link-time flags (don't need any..)
LFLAGS=

# Command for compilation
CPP=g++

# Command for linking
LINK=g++

# Location of a non-awful tar program
TAR=/usr/local/gnu/bin/tar

# Our final program name
APP=TBN

# Object files needed to build APP
OFILES=Main.o TestBignum.o Bignum.o

# Files for which changes should force everything to be remade:
ALLDEP=Makefile

# By default, build and test at level 6, which is the last required level
# Tests at up to test9 are available
all:	test6

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
	$(TAR) cvzf ../$(APP)-$(VERSION).tgz *

testlevel:
	@echo "BUILDING at level $(TESTLEVEL)"; \
	CFLAGS="-DTESTLEVEL=$(TESTLEVEL)" $(MAKE) -W TestBignum.C $(APP); \
	status=$$?; \
	if test $$status -ne 0; then \
	 echo "BUILD FAILED at level $(TESTLEVEL)"; \
         if test $(TESTLEVEL) -ne 0; then \
	  echo " Perhaps you want to try building at a lower test level."; \
          echo " For example, type '$(MAKE) test0' to build a test level 0"; \
	 fi; \
	else \
	 echo "BUILT SUCCESSFULLY at level $(TESTLEVEL)"; \
	 $(MAKE) test; \
	fi; \
	exit $$status

test:	$(APP)
	@echo "TESTING at level $(TESTLEVEL)"; \
	./$(APP); \
	status=$$?; \
	if test $$status -ne 0; then \
	echo "SOME TEST(S) FAILED AT LEVEL $(TESTLEVEL)"; else \
	 echo "PASSED ALL TESTS at level $(TESTLEVEL)"; fi; \
	exit $$status

# limited testing
test0:	
	@export TESTLEVEL=0; $(MAKE) testlevel
test1:	
	@export TESTLEVEL=1; $(MAKE) testlevel
test2:	
	@export TESTLEVEL=2; $(MAKE) testlevel
test3:	
	@export TESTLEVEL=3; $(MAKE) testlevel
test4:	
	@export TESTLEVEL=4; $(MAKE) testlevel
test5:	
	@export TESTLEVEL=5; $(MAKE) testlevel
test6:	
	@export TESTLEVEL=6; $(MAKE) testlevel
test7:	
	@export TESTLEVEL=7; $(MAKE) testlevel
test8:	
	@export TESTLEVEL=8; $(MAKE) testlevel
test9:	
	@export TESTLEVEL=9; $(MAKE) testlevel

#######
# Other dependencies (beyond each .C depending on its own .h)
main.o:	TestBignum.h

TestBignum.o: Bignum.h
