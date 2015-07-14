#ifndef TESTBIGNUM_H        /* -*- C++ -*- */
#define TESTBIGNUM_H

#ifndef __GNUC__
#error "Professor Ackley says: This code is intended for g++ only!"
#error "If you are seeing this error, you are NOT using g++!"
#endif

#include "Bignum.h"

#ifndef TESTLEVEL        /* Assume max testlevel if they didn't tell us one */
#define TESTLEVEL 9              
#endif

#include <stddef.h>      /* Added: Fri Mar 17 09:39:50 2000 for NULL */
class TestBignum {
 public:
  bool Run();			      // return true if any failed tests
  TestBignum();
 private:
  TestBignum(const TestBignum&);      // Declare away
  void operator=(const TestBignum&);  // Declare away
  void _MainTests();
  void _LeakTest();
  void _CheckCtors1();
  void _CheckDtor();
  void _CheckAssign();
  void _CheckElement();
  void _CheckOutput();
  void _CheckRead();
  void _CheckEqual();
  void _CheckAddition();
  void _CheckSubtraction();
  void _CheckCompare();
  void _CheckMultiplication();
  void _CheckDivision();
  void _SpeedTest();

  void _Test(const char * name, bool result, int sub = -1, char * p = NULL);
  void _Msg(const char * msg);

  bool _CheckBignum(Bignum&,int);
  bool _CheckBignum(Bignum&,char *);
  bool _MatchString(Bignum&,const char *);
  bool _Zero(Bignum&);
  char * _WriteBignum(Bignum&);
  void _CheckCtor(Bignum&,int);
  void _CheckCtor(Bignum&,char *);

  bool _Test10(Bignum&);
  bool _Test73(Bignum&);

  int _tests;			// Total tests run
  int _passed;			// Count of tests passed 
  int _failed;			// Count of tests failed
  bool _leaktest;		// True while we're doing the leak test 
  enum {_BUFSIZE=10 };	
  Bignum * _buf[_BUFSIZE];	// Room to hold some Bignum's
};
#endif
