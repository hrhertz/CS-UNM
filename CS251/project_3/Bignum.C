/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 3
*
* Ken Segura
* Userid: ksegura
*
********************************************************************
*
* Bignum.C
*
*******************************************************************
* Ken Segura
* ksegura@hackingtools.org
* http://www.hackingtools.org
*******************************************************************/ 

#include <iostream.h>
#include <iomanip.h>
#include <stddef.h>
#include <assert.h>
#include <strstream.h>
#include <string.h>
#include "Bignum.h"

Bignum::Bignum()
{

}


Bignum::Bignum(const Bignum &b)
{
  //cerr << "Bignum::Bignum(const Bignum &b)" << endl;
  _BigInt.Empty();
  *this = b; 
  //_BigInt.Debug();  // Print Debuging Info!
}


Bignum::Bignum(int i)
{
  //cerr << "Bignum::Bignum(int i)" << endl;
  int tmpint, modint = 0;
  //if < 0 set minus flag.
  tmpint = abs(i);
  while (tmpint != 0) {
    modint = (tmpint%10);
    _BigInt.InsertL(modint);
    tmpint = tmpint - modint;
    tmpint = tmpint/10;
  } 
  //_BigInt.Debug();  // Print Debuging Info!
}


Bignum::Bignum(const char * p)
{
  //cerr << "Bignum::Bignum(const char * p)" << endl;
  istrstream s(p,strlen(p));     // Make a stream on top of the string
  s >> *this;                    // Extract from that stream into us
  //if (!s) assert(0);             // Better defend against bogosity. 
  //_BigInt.Debug();  // Print Debuging Info!  
}


Bignum::~Bignum()
{

}


////// Deque ///////////////////
//
// CS251 Program 2, Spring 2000
// Ken Segura
// ksegura@unm.edu 

Bignum::_Deque::_Deque()
{
  _Tail = _Head = new _Ary('0',NULL,NULL);
  Sign = 0;
}


Bignum::_Deque::~_Deque()
{
  Empty();
  delete _Head;  
}             

///////////////////
// Not Implimented (Delete before handing in!)
/*Bignum::_Deque &Bignum::_Deque::operator=(const Bignum::_Deque &f)
{
  Stack & Stack::operator=(const Stack & s) {
    if (this==&s) return *this;                  // shortcut self-assignment
    Empty();                                     // Flush ourselves out
    if (f._head) f._head->ReverseInsert(*this);  // Fill w/s's stuff
    return *this;                                // Done
  }
  
  //void Stack::_Elt::ReverseInsert(Stack & t) {
  //  if (next) next->ReverseInsert(t); // Base case is next==NULL
  //  t.Insert(data);               // O(1) Insert-at-head
  //}              

}*/

////////
// _Ary
Bignum::_Deque::_Ary::_Ary(int ti, _Ary * pn, _Ary * pp)
{
  i = ti; next = pn; prev = pp;
}

Bignum::_Deque::_Ary::~_Ary()
{ }
// _Ary
////////

int * Bignum::_Deque::Read_Deque() const
{
  int * ti = NULL;
  int loop2 = 1;
  int Exp = 0;

  if (!IsEmpty()) {
  for (_Ary *loop = _Head; loop!= _Tail; loop = loop->next) {
   Exp++; }
  }

  ti = new int[(Exp+1)];
  ti[0] = Exp;

  for (_Ary *loop = _Head; loop!= _Tail; loop = loop->next) {
    ti[loop2] = loop->i;
    //cerr << "Val> " << ti[(loop2)] << " Index> " << (loop2) << " :: "; 
    loop2++;
  }
  if (Sign == 1) { ti[0] = ti[0] * (-1); }
    return (ti);
}

void Bignum::_Deque::InsertL(int i)
{
  _Ary * Node;
  Node = new _Ary(i,_Head,NULL);
  _Head->prev = Node;
  _Head = Node;
}      

int Bignum::_Deque::RemoveL()
{
  assert (!IsEmpty());
  int ti;
  _Ary * Node;
  Node = _Head;
  ti = Node->i;
  _Head = Node->next;
  _Head->prev = NULL;
  delete Node;
  return ti;
}           

void Bignum::_Deque::InsertR(int i)
{
  _Ary * Node;
  if (IsEmpty()) {
    InsertL(i);
  }
  else {
    Node = new _Ary(i,_Tail,_Tail->prev);
    _Tail->prev->next = Node;
    _Tail->prev = Node;
  }
}            

int Bignum::_Deque::RemoveR()
{
  assert (!IsEmpty());
  int ti;
  _Ary * Node;
  Node = _Tail->prev;
  if (Node->prev == NULL) {
    return RemoveL(); }
  else {
    ti = Node->i;
    Node->prev->next = _Tail;
    _Tail->prev = Node->prev;
    delete Node;
    return ti; }
}


void Bignum::_Deque::Debug() const
{
  cout << endl << "void Bignum::_Deque::Debug()" << endl;
  int Exp = 0;
  for (_Ary *loop = _Head; loop!=_Tail; loop = loop->next) {
    cout << loop->i << "-"; Exp++;}
  cout << endl;
  cout << "Exp = " << Exp << endl;
  cout << "_Head = " << _Head << endl;
  cout << "_Tail = " << _Tail << endl;
}

bool Bignum::_Deque::IsEmpty() const
{
  return (_Head == _Tail);
}   

void Bignum::_Deque::Empty()
{
  _Ary * Node;
  while(!IsEmpty()) {
    Node = _Head;
    _Head = Node->next;
    _Head->prev = NULL;
    delete Node;
  }
}

//
////// End Deque ////////////////


Bignum Bignum::Add(Bignum BigInt)
{
  // *this  ->> Current Object.
  // BigInt ->> NigInt to add to *this
  // TmpInt ->> Answer to be returned.
  // Go threw *this and add each element to BigInt.
  // Logic for Cary, Over and Sign.  

  Bignum TmpBigInt;

  int * pi = NULL;
  int * pi2 = NULL;
  int Exp_Sign = 0;
  int Exp_Sign2 = 0; 

  pi = _BigInt.Read_Deque();
  Exp_Sign = pi[0];

  pi2 = BigInt._BigInt.Read_Deque();
  Exp_Sign2 = pi2[0];   
  
  if (Exp_Sign == Exp_Sign2) {     
    for (int loop = 1; loop != (abs(Exp_Sign+1)); loop++) {
      TmpBigInt._BigInt.InsertL(pi[loop]+pi2[loop]); } }
  
  if (Exp_Sign > Exp_Sign2) {
    for (int loop = 1; loop != (abs(Exp_Sign2+1)); loop++) {
      TmpBigInt._BigInt.InsertL(pi[loop]+pi2[loop]); } }
  
  if (Exp_Sign < Exp_Sign2) {
    for (int loop = 1; loop != (abs(Exp_Sign+1)); loop++) {
      TmpBigInt._BigInt.InsertL(pi[loop]+pi2[loop]); } }
  
  delete [] pi;
  delete [] pi2;
  return TmpBigInt;

}

Bignum Bignum::Subtract(Bignum BigInt)
{
  //*this  ->> Current Object.
  //BigInt ->> NigInt to add to *this
  //TmpInt ->> Answer to be returned.
  //Go threw *this and subtract each element to BigInt.
  //Logic for Cary, Over and Sign.

  Bignum TmpBigInt;

  //int * pi;
  //int * pi2;
  //pi = _BigInt.Read_Deque();
  //pi2 = BigInt._BigInt.Read_Deque();
  //delete [] pi;
  //delete [] pi2;

  return TmpBigInt;

}


Bignum &Bignum::operator=(const Bignum &i)
{
  //cerr << "Bignum &Bignum::operator=(const Bignum &i)" << endl;

  int * pi = NULL;
  int Exp_Sign = 0;

  _BigInt.Empty();

  pi = i._BigInt.Read_Deque();
  Exp_Sign = pi[0];

  // Implement Sign...
  
  if (abs(Exp_Sign) != 0) {
    for (int loop = 1; loop != (abs(Exp_Sign+1)); loop++) {
      _BigInt.InsertR(pi[loop]);
    }
  } else { _BigInt.InsertR(0); }   

  delete [] pi;

  //_BigInt.Debug(); //Print Debuggin Info

  return *this;
}



Bignum &Bignum::operator=(const int n)
{
  //cerr << "Bignum &Bignum::operator=(const int n)" << endl;
  _BigInt.Empty();
  int tmpint, modint = 0;
  //if < 0 set minus flag.
  tmpint = abs(n);
  while (tmpint != 0) {
    modint = (tmpint%10);
    _BigInt.InsertL(modint);
    tmpint = tmpint - modint;
    tmpint = tmpint/10;
    }
  //_BigInt.Debug();  // Print Debuging Info! 
  return *this;
}


Bignum &Bignum::operator=(const char * p)
{
  //cerr << "Bignum &Bignum::operator=(const char * p)" << endl;
  istrstream s(p,strlen(p));     // Make a stream on top of the string
  s >> *this;                    // Extract from that stream into us
  //if (!s) assert(0);             // Better defend against bogosity.
  //_BigInt.Debug();  // Print Debuging Info!  
  return *this;
}


Bignum &Bignum::operator+=(const Bignum &i)
{
  //Carry not Implimented.  

  //cerr << "Bignum &Bignum::operator+=(const Bignum &i)" << endl;
  Bignum TmpBigInt;

  int * pi = NULL;
  int Exp_Sign = 0;

  int * pi2 = NULL;
  int Exp_Sign2 = 0;

  pi = _BigInt.Read_Deque();
  Exp_Sign = pi[0];

  pi2 = i._BigInt.Read_Deque();
  Exp_Sign2 = pi2[0];
  
  for (int loop = 1; loop != (abs(Exp_Sign+1)); loop++) {
    TmpBigInt._BigInt.InsertL(pi[loop]); }
  
  _BigInt.Empty();
  delete [] pi;
  pi = TmpBigInt._BigInt.Read_Deque();
  Exp_Sign = pi[0];   
  
  //if (Exp_Sign == Exp_Sign2) {
    for (int loop = abs(Exp_Sign+1); loop != 1; loop--) {
      _BigInt.InsertR(pi[loop]+pi2[loop]); }
    //}  
  
    //if (Exp_Sign > Exp_Sign2) {
    //for (int loop = 1; loop != (abs(Exp_Sign2+1)); loop++) {
    //_BigInt.InsertL(pi[loop]+pi2[loop]); } }
  
    //if (Exp_Sign < Exp_Sign2) {
    //for (int loop = 1; loop != (abs(Exp_Sign+1)); loop++) {
    //_BigInt.InsertL(pi[loop]+pi2[loop]); } }
  
  delete [] pi;
  delete [] pi2;
  return *this;
}


Bignum &Bignum::operator-=(const Bignum &i)
{
  //cerr << "Bignum &Bignum::operator-=(const Bignum &i)" << endl;
  return *this;
}


Bignum Bignum::operator+(const Bignum &b) const
{

  //Carry not Implimented.

  //cerr << "Bignum Bignum::operator+(const Bignum &b) const" << endl;
  Bignum TmpBigInt;

  int * pi = NULL;
  int * pi2 = NULL;
  int Exp_Sign = 0;
  int Exp_Sign2 = 0;

  pi = _BigInt.Read_Deque();
  Exp_Sign = pi[0];

  pi2 = b._BigInt.Read_Deque();
  Exp_Sign2 = pi2[0];

  if (Exp_Sign == Exp_Sign2) {
    for (int loop = (abs(Exp_Sign+1)); loop!= 0; loop--) {

      TmpBigInt._BigInt.InsertL(pi[loop]+pi2[loop]); } }

  if (Exp_Sign > Exp_Sign2) {
    for (int loop = 1; loop != (abs(Exp_Sign2+1)); loop++) {
      TmpBigInt._BigInt.InsertL(pi[loop]+pi2[loop]); } }

  if (Exp_Sign < Exp_Sign2) {
    for (int loop = 1; loop != (abs(Exp_Sign+1)); loop++) {
      TmpBigInt._BigInt.InsertL(pi[loop]+pi2[loop]); } }

  delete [] pi;
  delete [] pi2;
  return TmpBigInt;
}


Bignum Bignum::operator-(const Bignum &b) const
{
  //cerr << "Bignum Bignum::operator-(const Bignum &b) const" << endl;
  return *this;
}


bool Bignum::operator==(const Bignum &b) const
{
  //cerr << "bool Bignum::operator==(const Bignum &b) const" << endl;
  return true;
}


bool Bignum::operator!=(const Bignum &b) const
{
  //cerr << "bool Bignum::operator!=(const Bignum &b) const" << endl;
  return false;
}


bool Bignum::operator<(const Bignum &b) const
{
  //cerr << "bool Bignum::operator<(const Bignum &b) const" << endl;
  bool return_val;

  return return_val;
}


bool Bignum::operator<=(const Bignum &b) const
{
  //cerr << "bool Bignum::operator<=(const Bignum &b) const" << endl;
  bool return_val;

  return return_val;
}


bool Bignum::operator>(const Bignum &b) const
{
  //cerr << "bool Bignum::operator>(const Bignum &b) const" << endl;
  bool return_val;

  return return_val;
}

bool Bignum::operator>=(const Bignum &b) const
{
  //cerr << "bool Bignum::operator>=(const Bignum &b) const" << endl;
  bool return_val;

  return return_val;
}

ostream& operator<<(ostream& os, const Bignum& BigInt)
{
  int * pi = NULL;
  int Exp_Sign = 0;

  pi = BigInt._BigInt.Read_Deque();
  Exp_Sign = pi[0];

  //BigInt._BigInt.Debug();  // Print Debuging Info!

  //if (Exp_Sign < 0) { os << "-"; }

  if (abs(Exp_Sign) != 0) {
    for (int loop = 1; loop != (abs(Exp_Sign+1)); loop++) {
      os << (pi[loop]);    
    }
  } else { os << Exp_Sign; }
  
  delete [] pi;
  return os; 
}


istream& operator>>(istream& in, Bignum& BigInt)
{
  int kybd_in = 0;
  
  kybd_in = in.get();  
  if (kybd_in == 45) {               // See if the Bignum is Negative
  } else {
    in.putback(kybd_in); }           // If not put it back.

  kybd_in = 0;
 
  kybd_in = in.get();
  if (kybd_in == 32 || kybd_in == 43 || kybd_in == '\t' || kybd_in == '\n')
    { // Eat leading space and go on.
  } else {
    in.putback(kybd_in); }           // If not put it back.

  kybd_in = 0;

  while ((kybd_in = in.get()) != '\n') {
    
    ////////////////////////////////////////////
    //(kybd_in - 48) Converts from ASCII to int.
    // 0 = 48 ... 9 = 57
    
    if (((kybd_in-48) < 0) || ((kybd_in-48) > 9)) {
      //assert(0);
      in.set(ios::badbit);
      return in;
    }
    
    BigInt._BigInt.InsertR((kybd_in-48));
    kybd_in = 0;
  }
  //BigInt._BigInt.Debug();  // Print Debuging Info!
  return in;
}


