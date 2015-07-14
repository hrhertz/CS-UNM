/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 4
*
* Ken Segura
* Userid: ksegura@unm.edu
*
********************************************************************
*
* Label.C
*
*******************************************************************/
                                                                   
#include "Label.h"

Label::Label()
{
  _Tail = _Head = new _Ary('0',NULL,NULL); 
}


Label::Label(int len)
{
  _Tail = _Head = new _Ary('0',NULL,NULL);
}

Label::Label(const Label &d)
{

  _Tail = _Head = NULL;
  *this = d;

}

Label &Label::operator=(const Label & d)
{
  if (this==&d) { return *this; }

  _Empty();

  if (!IsEmpty()) {
    for (_Ary * loop = d._Head; loop!=d._Tail; loop = loop->next) {
      InsertL(loop->ch);
    } }
  return *this;     
}

Label::~Label()
{

  _Empty(); 

}

/////////////
Label::_Ary::_Ary(char tch, _Ary * pn, _Ary * pp)
{
  ch = tch;
  next = pn;
  prev = pp;
}

Label::_Ary::~_Ary()
{
} 
////////////

void Label::InsertL(char ch)
{
  _Ary * Node;
  Node = new _Ary(ch,_Head,NULL);
  _Head->prev = Node;
  _Head = Node;
}     

char Label::RemoveL()
{
  if (IsEmpty()) { exit(1); return false; }
  char tch;
  _Ary * Node;
  Node = _Head;
  tch = Node->ch;
  _Head = Node->next;
  _Head->prev = NULL;
  delete Node;
  return tch;
}  

void Label::InsertR(char ch)
{
  _Ary * Node;
  if (IsEmpty()) {
    InsertL(ch);
  }
  else {
    Node = new _Ary(ch,_Tail,_Tail->prev);
    _Tail->prev->next = Node;
    _Tail->prev = Node;
    //_Index++;
  }
}     

char Label::RemoveR()
{
  if (IsEmpty()) { exit(1); return false; }
  char tch;
  _Ary * Node;
  Node = _Tail->prev;
  if (Node->prev == NULL) {
    return RemoveL(); }
  else {
    tch = Node->ch;
    Node->prev->next = _Tail;
    _Tail->prev = Node->prev;
    delete Node;
    return tch; }
}     

bool Label::IsEmpty() const
{
  return (_Head == _Tail);
}  

void Label::_Empty()
{
  _Ary * Node;
  while(!IsEmpty()) {
    Node = _Head;
    _Head = Node->next;
    _Head->prev = NULL;
    delete Node;
  }
 
}     

char * Label::Read_Label() const
{
  char * ti = NULL;
  int loop2 = 1;
  int Exp = 0;

  if (!IsEmpty()) {
    for (_Ary *loop = _Head; loop!= _Tail; loop = loop->next) {
      Exp++; }
  }

  ti = new char[(Exp+1)];
  ti[0] = Exp;

  for (_Ary *loop = _Head; loop!= _Tail; loop = loop->next) {
    ti[loop2] = loop->ch;
    loop2++;
  }
  return ti;
}                   


ostream& operator<<(ostream& os,const Label & d)
{
  char * pi = NULL;
  int Exp_Sign = 0;

  pi = d.Read_Label();
  Exp_Sign = pi[0];

  if (Exp_Sign != 0) {
    for (int loop = 1; loop != (Exp_Sign+1); loop++) {
      os << (pi[loop]);
    }
  }

  delete [] pi;   
 
  return os;
}

istream& operator>>(istream& in,Label & d)
{
  int i = 0;

  char ch;

  in >> i; if (!cin) exit(1);

  in >> ch; if (!cin) exit(1); 

  for(int loop = 0; loop < i; loop++) {
    in >> ch; d.InsertR(ch); }

  return in;
}
