#include "TestBignum.h"
#include <assert.h>
#include <strstream.h>		/* for ostrstream, istrstream */
#include <unistd.h>		/* for sbrk */ 

///////// 
// PUBLIC INTERFACE
//

// Our ctor
TestBignum::TestBignum() {
  _tests = _passed = _failed = 0;
  _leaktest = false;
  for (int i = 0; i<_BUFSIZE; ++i) _buf[i] = NULL;
}

// Run the whole show
bool TestBignum::Run()
{
  _MainTests();
  _LeakTest();
  _SpeedTest();
  cerr << "Tests=" << _tests
       << " PASSED=" << _passed
       << " FAILED=" << _failed
       << endl;
  if (_failed==0) 
    cerr
      << endl
      << "+----------------------------------------------------+" << endl
      << "| ALL TESTS PASSED AT TESTLEVEL " << TESTLEVEL << "!  CONGRATULATIONS! |" << endl
      << "+----------------------------------------------------+" << endl
      << endl;
  return _failed!=0;
}

///////// 
// MAIN TEST DRIVERS
//

// A disgusting macro so we can make failed tests look like compilation errors
static char * testfilename;
static int testlineno;
#define DOTEST(ARGS) \
  do { testfilename = __FILE__; testlineno = __LINE__; _Test ARGS ; } while (0)

// Test everything except leaks
void TestBignum::_MainTests()
{
  _CheckCtors1();
  _CheckDtor();
  _CheckOutput();
  _CheckAssign();
  _CheckEqual();
  _CheckRead();
  _CheckAddition();
  _CheckSubtraction();
  _CheckCompare();
  _CheckMultiplication();
  _CheckDivision();
}

// Test for leaks by rerunning the main tests several times
//  and checking that our overall heap size hasn't get any
//  bigger.  Go through the loop once before picking up the
//  start size to give the heap yet more time to setle.
void TestBignum::_LeakTest()
{
  _Msg("\tLEAKS..");
  _leaktest = true;
  void * initial;
  for (int i = 0; i<20; ++i) {
    _MainTests();
    if (i==0) initial = sbrk(0);
  }
  void * final = sbrk(0);
  _leaktest = false;
  DOTEST(("Leak test",final<=initial,
	  static_cast<char*>(final)-static_cast<char*>(initial)));
}

///////// 
// TESTING HELPER ROUTINES 
//

// Our main test reporting routine.  Does nothing if we're testing for leaks. 
//   Not called directly.  Called via DOTEST to set up testfilename and
//   testlineno.
void TestBignum::_Test(const char * name, bool result, int sub, char * msg)
{
  if (_leaktest) return;
  ++_tests;
  if (result) {
    ++_passed;
  } else {
    cerr << testfilename << ":" << testlineno;
    cerr << " FAILED: ";
    ++_failed;
    cerr << name;
    if (sub>=0) cerr << " (" << sub << ")";
    if (msg) cerr << " [" << msg << "]";
    cerr << endl;
  }
}

// Print a message unless we're leak testing
void TestBignum::_Msg(const char *msg)
{
  if (_leaktest) return;
  cerr << msg << endl;
}

// Using op<<(ostream&,Bignum&), write Bignum 'b' out to
//   a global string and return a pointer to that string.
//   Dies if called while TESTLEVEL==0 since that means
//   a bug in the TestBignum.
char * TestBignum::_WriteBignum(Bignum & b)
{
#if TESTLEVEL>=1
  enum {BignumBUFSIZE=10000};
  static char Bignumbuf[BignumBUFSIZE];	// static so we can return ptr to it
  ostrstream s(Bignumbuf,BignumBUFSIZE);
  s << b << ends;
  return Bignumbuf;
#else
  assert(0);
  return NULL;
#endif
}

// Return true if Bignum 'b' prints out a form identical to 
//   string 'q', which must be in strict standard format.  
//   Uses _WriteBignum so unusable if TESTLEVEL==0.
bool TestBignum::_MatchString(Bignum &b, const char * q)
{
  return !strcmp(_WriteBignum(b),q);
}

// Return true if Bignum 'b' is 0.  Uses _WriteBignum
// so unusable if TESTLEVEL==0.
bool TestBignum::_Zero(Bignum &b)
{
  return _MatchString(b,"0");
}

// Test if Bignum 'b' contains just the int 'i'.  Uses
//   _WriteBignum so unusable if TESTLEVEL==0.
void TestBignum::_CheckCtor(Bignum & b, int i)
{
  char buf[100];
  ostrstream s(buf,100);
  s << i << ends;
  DOTEST(("Bignum(int)",_MatchString(b,s.str()),i));
}

// Test if Bignum 'b' prints out a form identical to string 'q', 
//   which must be in strict standard format.  Uses
//   _WriteBignum so unusable if TESTLEVEL==0.
void TestBignum::_CheckCtor(Bignum & b, char * q)
{
  DOTEST(("Bignum(char*)",_MatchString(b,q),-1,q));
}

// Test if Bignum 'b' is the number 123456789. Uses
//   _WriteBignum so unusable if TESTLEVEL==0.
bool TestBignum::_Test10(Bignum & b)
{
  return _MatchString(b,"123456789");
}

// Test if Bignum 'b' is the number 73. Uses
//   _WriteBignum so unusable if TESTLEVEL==0.
bool TestBignum::_Test73(Bignum & b)
{
  return _MatchString(b,"73");
}

///////// 
// SPECIFIC FUNCTION TESTS
//

// Test Bignum(), Bignum(int), Bignum(Bignum&), and Bignum(char *)
//   Note that at TESTLEVEL==0, we can barely actually test anything
void TestBignum::_CheckCtors1()
{
  _Msg("\tBASIC CTORS..");     
  // We'll hold these Bignum's for now, rather than
  // deleting them immediately, to avoid testing the dtor yet 
  _buf[0] = new Bignum;
  DOTEST(("Bignum()", true));

  _buf[1] = new Bignum(73);
#if TESTLEVEL>=1
  DOTEST(("Bignum(int)", _Test73(*_buf[1])));
#else
  DOTEST(("Bignum(int)", true));
#endif

#if TESTLEVEL>=1  /* Could do this at 0 but _CheckCtor needs 1 */
  for (int i = 1; i < 200000000; i <<= 3) {
    Bignum t(i); _CheckCtor(t,i);
#if TESTLEVEL>=8
    Bignum m(-i); _CheckCtor(m,-i);
#endif
  }
#endif

#if TESTLEVEL>=2
  _buf[2] = new Bignum(*_buf[1]);
  DOTEST(("Bignum(const Bignum &)", _Test73(*_buf[2])));
#endif

#if TESTLEVEL>=3
  _buf[3] = new Bignum("         +73");
  DOTEST(("Bignum(const char *)", _Test73(*_buf[3])));
#endif

}

// Test ~Bignum().  At this point about all we can do is
//   see if we crash.  If not we declare the test passed. 
//   (If the dtor's not doing its job, we'll catch it
//   in the leak test.  If it's doing its job wrong, we'll
//   hopefully crash *somewhere*.)
void TestBignum::_CheckDtor()
{
  _Msg("\tDTOR..");            
  for (int i = 0; i<_BUFSIZE; ++i) {
    if (_buf[i]) {
      delete _buf[i];
      _buf[i] = NULL;
      DOTEST(("~Bignum()", true, i));
    }
  }
}

// Test operator<<(ostream&,Bignum&).  Note that since so
//   much of the testing depends on being able to output
//   Bignums in standard format, this operator must exist and
//   be correct very early in the development.
void TestBignum::_CheckOutput()
{
#if TESTLEVEL>=1
  _Msg("\tOSTREAM<<..");       
  Bignum e;
  DOTEST(("operator<<(ostream&,Bignum&)",_Zero(e)));

  Bignum i(73);
  DOTEST(("operator<<(ostream&,Bignum&)",_Test73(i)));

  // Check that op<< is returning the right type and value
  {
    char buf[1000];
    ostrstream s(buf,1000);
    s << i << ',' << i << ends;
    DOTEST(("operator<<(ostream&,Bignum&)",!strcmp(s.str(),"73,73")));  
  }

#if TESTLEVEL>=8
  {
    char buf[1000];
    ostrstream s(buf,1000);
    i = -i;
    s << i << i << ends;
    DOTEST(("operator<<(ostream&,Bignum&)",!strcmp(s.str(),"-73-73")));
  }
#endif  
#endif

#if TESTLEVEL>=3
  Bignum j("0123456789");
  DOTEST(("operator<<(ostream&,Bignum&)",_Test10(j)));
#endif
}

// Test op= in a variety of ways
void TestBignum::_CheckAssign()
{
  _Msg("\tASSIGN OPS..");      
  {
    Bignum bi, bj;
    bi = 9;
    bj = 0;
    DOTEST(("op=(int)",true));  // well, we didn't segfault yet...
#if TESTLEVEL>=1
    DOTEST(("op=(int)",_MatchString(bi,"9"),1));  
    DOTEST(("op=(int)",_MatchString(bj,"0"),2));  
#endif
#if TESTLEVEL>=8
    bi = -9;
    DOTEST(("op=(int)",_MatchString(bi,"-9"),1));  
#endif
  }
#if TESTLEVEL>=2
  {
    Bignum bi, bj;
    bj = bi;
    DOTEST(("op=(Bignum)",_Zero(bj)));
  }
  {
    Bignum bi(13), bj;
    bj = bi;
    DOTEST(("op=(Bignum)",_MatchString(bj,"13"),1));
  }
  {
    Bignum bi;
    bi = bi;
    DOTEST(("op=(Bignum) (self)",_Zero(bi),2));
    Bignum bj(12);
    bj = bi;
    bi = bj;
    bi = bi;
    DOTEST(("op=(Bignum) (self)",_Zero(bi),3));
  }
  {
    Bignum bi;
    for (int i = 0; i<=73; ++i)
      bi = i;
    DOTEST(("op=(int)",_Test73(bi)));
  }
#endif

}

// Test Bignum(char*), op=(char *), and operator>>(istream&,Bignum&)
void TestBignum::_CheckRead()
{
#if TESTLEVEL>=3
  _Msg("\tISTREAM>>..");       
  char * (tests[]) = {
    "0",
    "-1",
    "-110000000",
    "1234567891011121314151617181920",
    "12345678910" 
     "11121314151617181920"
     "21222324252627282930"
     "31323334353637383940"
     "41424344454647484950"
     "51525354555657585960"
     "61626364656667686970"
     "71727374757677787980"
     "81828384858687888990"
     "919293949596979899",
    NULL};
  for (int i = 0; tests[i]; ++i) 
  {
#if TESTLEVEL<8
    if (tests[i][0]=='-') continue;
#endif    
    Bignum t(tests[i]);
    _CheckCtor(t,tests[i]);
    t = 0;
    _CheckCtor(t,"0");
    t = tests[i];
    _CheckCtor(t,tests[i]);

    istrstream s(tests[i]);
    s >> t;
    DOTEST(("operator>>(istream&,Bignum&)",_MatchString(t,tests[i]),i));
  }
  {
    istrstream s(" \n\t0123456789");
    Bignum t;
    s >> t;
    DOTEST(("operator>>(istream&,Bignum&) (leading whitespace)",_Test10(t)));
  }
  {
    istrstream s(" \n\t+000000000000123456789");
    Bignum t;
    s >> t;
    DOTEST(("operator>>(istream&,Bignum&) (leading whitespace/zeros)",_Test10(t)));
  }
  {
    istrstream s(" \n\t000000000000073");
    Bignum t;
    s >> t;
    DOTEST(("operator>>(istream&,Bignum&) (leading whitespace/zeros)",_Test73(t)));
  }
  {
    istrstream s(" \n\t            0");
    Bignum t;
    s >> t;
    DOTEST(("operator>>(istream&,Bignum&) (leading whitespace)",_Zero(t)));
  }
  {
    istrstream s("123456789 73 0");
    Bignum a,b,c;
    s >> a >> b >> c;
    DOTEST(("operator>>(istream&,Bignum&) (first/multiple)",_Test10(a)));
    DOTEST(("operator>>(istream&,Bignum&) (second/multiple)",_Test73(b)));
    DOTEST(("operator>>(istream&,Bignum&) (third/multiple)",_Zero(c)));
  }
  {
    istrstream s("123456789,73:0");
    Bignum a;
    char ch;
    s >> a;
    DOTEST(("operator>>(istream&,Bignum&) (first,multiple)",_Test10(a)));
    s >> ch;
    DOTEST(("operator>>(istream&,Bignum&) (delimiter,)",ch==','));    
    s >> a;
    DOTEST(("operator>>(istream&,Bignum&) (second:multiple)",_Test73(a)));
    s >> ch;
    DOTEST(("operator>>(istream&,Bignum&) (delimiter:)",ch==':'));    
    s >> a;
    DOTEST(("operator>>(istream&,Bignum&) (third multiple)",_Zero(a)));
    DOTEST(("operator>>(istream&,Bignum&) (end-of-input)",!s));
  }
#if TESTLEVEL>=8
  {
    istrstream s("+1-2+3-4");
    Bignum a,b,c,d;
    s >> a >> b >> c >> d;
    DOTEST(("operator>>(istream&,Bignum&) (+1/multiple)",_MatchString(a,"1")));
    DOTEST(("operator>>(istream&,Bignum&) (-2/multiple)",_MatchString(b,"-2")));
    DOTEST(("operator>>(istream&,Bignum&) (+3/multiple)",_MatchString(c,"3")));
    DOTEST(("operator>>(istream&,Bignum&) (-4/multiple)",_MatchString(d,"-4")));
  }
#endif  
#endif
}

// Test op== and op!=
void TestBignum::_CheckEqual()
{
#if TESTLEVEL>=4
  _Msg("\tEQUALITY..");        
  int test = 0;
  for (int i = 3; i < 100000000; i *= 27)
    for (int j = 3; j < 100000000; j *= 27) {
      Bignum bi(i), bj(j);
      DOTEST(("op==", (bi==bj)==(i==j), ++test));
      DOTEST(("op!=", (bi!=bj)==(i!=j), ++test));
      int start;
#if TESTLEVEL>=8
      start = -3;
#else
      start = 0;
#endif    
      for (int k = start; k<3; ++k) { bi += k; bj += k; }
      DOTEST(("op==", (bi==bj)==(i==j), ++test));
      DOTEST(("op!=", (bi!=bj)==(i!=j), ++test));
    }
#endif
}

void TestBignum::_CheckAddition()
{
#if TESTLEVEL>=4
  _Msg("\tADDITION OPS..");    
  {
    Bignum bi;
    int mult = 1;
    for (int i = 0;i<10;++i) { bi += (9-i)*mult; mult *= 10; }
    DOTEST(("op+=(int)",_Test10(bi)));
  }
  {
    Bignum bi, bj;
    int mult = 1;
    for (int i = 0;i<10;++i) {
      if (i&1) bi += (9-i)*mult;
      else bj += (9-i)*mult;
      mult *= 10;
    }
    bi += bj;
    DOTEST(("op+=(Bignum)",_Test10(bi)));
    Bignum bz;
    bi += bz;
    DOTEST(("op+=(Bignum)",_Test10(bi),1));
  }
  {
    Bignum bi, bj, bk;
    int mult = 1;
    for (int i = 0;i<10;++i) {
      if (i&1) bi += (9-i)*mult;
      else bj += (9-i)*mult;
      mult *= 10;
    }
    bk = bi+bj;
    DOTEST(("op+(Bignum,Bignum)",_Test10(bk)));
  }
#if TESTLEVEL>=8
  {
    Bignum bi(100),bj(-200),bk;
    bk = bj+bi;
    DOTEST(("op+(Bignum,Bignum) (-/+)",_MatchString(bk,"-100")));
    bk = bi+bj;
    DOTEST(("op+(Bignum,Bignum) (+/-)",_MatchString(bk,"-100")));
    bi += bj;
    DOTEST(("op+=(Bignum,Bignum) (+/-)",_MatchString(bi,"-100")));
  }
#endif

#endif  
}

void TestBignum::_CheckSubtraction()
{
#if TESTLEVEL>=5
  _Msg("\tSUBTRACTION OPS.."); 
  {
    Bignum bi(4);
    bi -= 4;
    DOTEST(("op-=(Bignum)",_Zero(bi)));
  }
#if TESTLEVEL>=8
  {
    Bignum bi, bj;
    for (int i = 1;i<32;++i) {
      bi += 1<<i;
      bj -= 1<<i;
    }
    bi += bj;
    DOTEST(("op-=(Bignum)",_Zero(bi),1));
    Bignum bz;
    bi -= bz;
    DOTEST(("op-=(Bignum)",_Zero(bi),2));
  }
#endif
  {
    Bignum bi;
    for (int i = 0;i<100; ++i) bi += i;
    for (int i = 0;i<100; ++i) bi -= i;
    DOTEST(("op-=(Bignum)", _Zero(bi),3));
  }
  {
    Bignum bi;
    for (int i = 0;i<100; ++i) bi += i;
    for (int i = 100-1;i>=0; --i) bi -= i;
    DOTEST(("op-=(Bignum)", _Zero(bi),4));
  }
  {
    Bignum bi, bj, bk;
    for (int i = 0;i<100;++i) {
      bi += 1000000000;
      bj += 1000000000;
    }
    bk = bi-bj;
    DOTEST(("op-(Bignum,Bignum)", _Zero(bk),1));
  }
#if TESTLEVEL<8
  // A few tests making sure we have zero-pinned behavior if no negs
  {
    Bignum bi(-100);
    DOTEST(("Bignum(-100)",_Zero(bi),1));

    Bignum bj(100);
    bj -= 200;
    DOTEST(("op-=(negative::zero)",_Zero(bj),1));

    Bignum bk("-100100");
    DOTEST(("Bignum(char * negative::zero)",_Zero(bk),1));

    Bignum bl;
    bl = Bignum(1)-Bignum(2);
    DOTEST(("op-(negative::zero)",_Zero(bl),1));

  }
#endif
#endif
}

void TestBignum::_CheckCompare()
{
#if TESTLEVEL>=6
  _Msg("\tCOMPARISON OPS..");      
  int test = 0;
  for (int i = 3; i < 100000000; i *= 27) 
    for (int j = -12345678; j < 12345678; j += 12345677) {
      Bignum bi(i), bj(j);
      int ti = i, tj = j;
#if TESTLEVEL<8
  if (ti<0) ti = 0;
  if (tj<0) tj = 0;
#endif
      DOTEST(("op<", (bi< bj) == (ti<tj), ++test));
      DOTEST(("op<=",(bi<=bj) == (ti<=tj), ++test));
      DOTEST(("op>", (bi> bj) == (ti>tj), ++test));
      DOTEST(("op>=",(bi>=bj) == (ti>=tj), ++test));
    }
#endif
}

void TestBignum::_CheckMultiplication()
{
#if TESTLEVEL>=7
  _Msg("\tMULTIPLICATION OPS..");      
  int test = 0;
  {
    Bignum bz(0),bo(1),bm;
    bm = bo;
    DOTEST(("op*=", bm == 1, ++test));
    bo *= bo;
    DOTEST(("op*=(self)", bo == 1, ++test));
    bm *= bm;
    DOTEST(("op*=(self)", bm == 1, ++test));
    bm *= bz;
    DOTEST(("op*=", bm == bz, ++test));
  }
#if TESTLEVEL>=8
  {
    Bignum bz(0),bo(1),bm(-1);
    bm *= bo;
    DOTEST(("op*=", bm == -1, ++test));
    bo *= bo;
    DOTEST(("op*=(self)", bo == 1, ++test));
    bm *= bm;
    DOTEST(("op*=(self)", bm == 1, ++test));
    bm *= bz;
    DOTEST(("op*=", bm == bz, ++test));
  }
#endif
  for (int i = 3; i < 10000; i *= 27)
    for (int j = -12345; j < 12345; j += 1234) {
      Bignum bi(i), bj(j);
      int ti = i, tj = j;
#if TESTLEVEL<8
  if (ti<0) ti = 0;
  if (tj<0) tj = 0;
#endif
      DOTEST(("op*", (bi*bj) == (ti*tj), ++test));
      DOTEST(("op*", (bj*bi) == (ti*tj), ++test));
      bi *= 1;
      DOTEST(("op*=", bi == ti, ++test));
#if TESTLEVEL>=8
      bi *= -1;
      DOTEST(("op*=", bi == -i, ++test));
      bi *= bj;
      DOTEST(("op*=", bi == -(i*j), ++test));
#endif
      bi *= 0;
      DOTEST(("op*=", bi == 0, ++test));
    }
  {
    Bignum a(2), b(2);
    for (int i = 0; i<127; ++i) a *= b;
    for (int i = 0; i<7; ++i) b *= b;
    DOTEST(("op*=", a == b, ++test));
  }
#endif
}

void TestBignum::_CheckDivision()
{
#if TESTLEVEL>=9
  _Msg("\tDIVISION OPS..");      
  int test = 0;
  {
    Bignum bz(0),bo(1),bm(-1);
    bm /= bo;
    DOTEST(("op/=", bm == -1, ++test));
    bo /= bo;
    DOTEST(("op/=(self)", bo == 1, ++test));
    bm /= bm;
    DOTEST(("op/=(self)", bm == 1, ++test));
    bz /= bm;
    DOTEST(("op*=", bz == 0, ++test));
  }

  for (int i = 3; i < 10000; i *= 27)
    for (int j = -12345; j < 12345; j += 1234) {
      Bignum bi(i), bj(j);
      int ti = i, tj = j;
      DOTEST(("op/", (bi/bj) == (ti/tj), ++test));
      DOTEST(("op/", (bj/bi) == (tj/ti), ++test));
      bi /= 1;
      DOTEST(("op/=", bi == ti, ++test));
      bi /= -1;
      DOTEST(("op/=", bi == -i, ++test));
      bi /= bj;
      DOTEST(("op/=", bi == -(i/j), ++test));
    }
  _Msg("\t\tMOD TESTS NOT YET IMPLEMENTED!!..");      

#endif
}

// Support for speed tests
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <math.h>		/* for sqrt */

struct tis_time {
  int sec;
  int usec;
};

void tis_gettime(struct tis_time & t)
{
  struct rusage ru;
  getrusage(RUSAGE_SELF,&ru);

  t.sec = ru.ru_utime.tv_sec;
  t.usec = ru.ru_utime.tv_usec;
}

double usecsper(int count,double overper,struct tis_time & start, struct tis_time & stop)
{
  return ((stop.sec - start.sec)*1000000 + (stop.usec - start.usec))/((double)count)-overper;
}

double tis_report(char * label, int count, double overper, struct tis_time & start, struct tis_time & stop)
{
  double time = usecsper(count,overper,start,stop);
  //  cerr << "  " << label;
  //  cerr << " (" << count << " trials) = " << time;
  //  cerr << " usec/trial";
  //  cerr << flush;
  return time;
}

const int speedtestusecs =  750000;       // How long to run the speed tests
const int speedtestpowers = 7;	          // How many powers of 2 to test
const int speedpowerbase = 32;	          // First power of 2 to test

void TestBignum::_SpeedTest()
{
  _Msg("\tSPEED TESTS..");

  int i, trials;
  struct tis_time start, stop;
  double nullspeed;
  double cdspeed;

  {
    tis_gettime(start);
    for (trials = 1;1;++trials) {
      tis_gettime(stop);
      if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
    }
    tis_gettime(stop);
    nullspeed = tis_report("Time loop calibration",trials,0.0,start,stop);
    //    cerr << endl;

    tis_gettime(start);
    for (trials = 1;1;++trials) {
      Bignum test;
      tis_gettime(stop);
      if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
    }

    tis_gettime(stop);
    cdspeed = tis_report("Empty ctor/dtor",trials,nullspeed,start,stop);
    //    cerr << endl;
  }

  char *(names[]) = {
#if TESTLEVEL>=3
    "READ",
#else
    NULL,
#endif
#if TESTLEVEL>=4 /* Fri Mar 24 13:18:27 2000 Ackley was >=3 */
    "COPY CTOR",
#else
    NULL,
#endif
#if TESTLEVEL>=4    
    "OP+=/OP+/OP==/OP!=",
#else
    NULL,
#endif
#if TESTLEVEL>=5
    "COPY/OP-/OP-=",
#else
    NULL,
#endif
#if TESTLEVEL>=6    
    "COPY/OP</OP<=/OP>/OP>=",
#else
    NULL,
#endif    
#if TESTLEVEL>=7    
    "OP*= (fixed size multiplicand)",
#else
    NULL
#endif
  };
  for (unsigned int speedtests = 0;speedtests<sizeof(names)/sizeof(names[0]); ++speedtests) {
    char * name = names[speedtests];

    if (!name) continue;
    double growtimes[speedtestpowers];
    double sum = 0.0;

    cerr << "\t " << name << " LINEARITY TEST " << endl;

    for (i = 0;i<speedtestpowers;++i) {
      int length = speedpowerbase<<i;
      ostrstream o;
      for (int k=0;k<length;++k) o << k%10;
      o << ends;

      switch (speedtests) {
      default: continue;
	
#if TESTLEVEL>=3
      case 0:
	{
	  char * str = o.str();
	  
	  tis_gettime(start);
	  for (trials = 1;1;++trials) {
	    testlineno = __LINE__; // Test code begins here
	    Bignum test(str);              //Bignum(char*);
	    tis_gettime(stop);
	    if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
	  }
	  tis_gettime(stop);
	  break;
	}
#endif	

#if TESTLEVEL>=4   /* Ackley: Changed Fri Mar 17 09:46:57 2000 was >=3 */
      case 1:
	{
	  Bignum bignum(o.str());
	  
	  tis_gettime(start);
	  for (trials = 1;1;++trials) {
	    testlineno = __LINE__; // Test code begins here
	    Bignum test(bignum);	// copy ctor
	    test += trials; 
	    tis_gettime(stop);
	    if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
	  }
	  tis_gettime(stop);
	  break;
	}
#endif	

#if TESTLEVEL>=4
      case 2:
	{
	  Bignum b(o.str());
	  
	  tis_gettime(start);
	  for (trials = 1;1;++trials) {
	    testlineno = __LINE__; // Test code begins here
	    Bignum test;		
	    test += b;		// op+=
	    test += b;		// op+=
	    test = test+b;	// op+
	    test==b;		// op==
	    test!=b;		// op!=
	    tis_gettime(stop);
	    if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
	  }
	  tis_gettime(stop);
	  break;
	}
#endif	

#if TESTLEVEL>=5
      case 3:
	{
	  Bignum b(o.str());
	  
	  tis_gettime(start);
	  for (trials = 1;1;++trials) {
	    testlineno = __LINE__; // Test code begins here
	    Bignum test(b);	// copy ctor
	    test-b;		// op-
	    test -= b;	// op-=
	    tis_gettime(stop);
	    if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
	  }
	  tis_gettime(stop);
	  break;
	}
#endif	

#if TESTLEVEL>=6
      case 4:
	{
	  Bignum b(o.str());
	  
	  tis_gettime(start);
	  for (trials = 1;1;++trials) {
	    testlineno = __LINE__; // Test code begins here
	    Bignum test(b);	// copy ctor
	    Bignum test2;	// default ctor
	    test < b;		// op<
	    test <= b;	// op<=
	    b < test2;
	    b <= test2;
	    test > b;		// op<
	    test >= b;	// op<=
	    b > test2;
	    b >= test2;

	    tis_gettime(stop);
	    if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
	  }
	  tis_gettime(stop);
	  break;
	}
#endif	

#if TESTLEVEL>=7
      case 5:
	{
	  Bignum b(o.str());
	  
	  tis_gettime(start);
	  for (trials = 1;1;++trials) {
	    testlineno = __LINE__; // Test code begins here
	    Bignum test(b);	// ctor
	    test *= 9;
	    test *= Bignum(-256);
	    tis_gettime(stop);
	    if (usecsper(1,0.0,start,stop)>speedtestusecs) break;
	  }
	  tis_gettime(stop);
	  break;
	}
#endif	
      }
      
      if (i==0) cerr << "\t   [n="; else cerr << " [";
      cerr << length;
      growtimes[i] =
	tis_report("",trials,cdspeed+nullspeed,start,stop)/length;
      cerr << ": " << static_cast<int>(growtimes[i]) << (i==0?" usecs/elt]":"]") << flush;
      sum += growtimes[i];
    }

    double avg = sum/speedtestpowers, sumsq = 0.0;
    for (i = 0;i<speedtestpowers; ++i) sumsq = (growtimes[i]-avg)*(growtimes[i]-avg);
    cerr << endl << "\t   Average = " << avg << " usec/elt";
    double sd = sqrt(sumsq/(speedtestpowers*speedtestpowers));
    cerr << "  Standard deviation = " << sd;
    cerr << endl;
    testfilename = __FILE__;
    _Test(name,sd<1.5,0,NULL);	// Not using DOTEST so we can refer errors earlier
  }
}
