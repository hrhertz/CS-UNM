// CS251 Program 2, Spring 2000
// Ken Segura
// ksegura@unm.edu

#include <iostream>
#include <cstdlib>
#include "Deque.h"

Deque::Deque()
{
  _MaxSize = 1;
  _Index  = 0;
  _Tail = _Head = new _Ary('0',NULL,NULL);
}


Deque::Deque(const Deque & f)
{
  /////////
  //Broken?

  _Tail = _Head = NULL;
  *this = f;
}

Deque &Deque::operator=(const Deque & f)
{ 
  //////////
  // Broken?
  
  if (this==&f) { return *this; }
  
  _Empty();
  _MaxSize = f._MaxSize; 

  if (!IsEmpty()) {  
  for (_Ary * loop = f._Head; loop!=f._Tail; loop = loop->next) { 
    InsertL(loop->ch);   
  } } 
  return *this;
}

Deque::~Deque()
{ 
  _Empty();
}


Deque::_Ary::_Ary(char tch, _Ary * pn, _Ary * pp)
{
  ch = tch;
  next = pn;
  prev = pp;
}

Deque::_Ary::~_Ary()
{
}

void Deque::InsertL(char ch)
{
  if (IsFull() == true) { _Error('I'); return; }
  _Ary * Node;
  Node = new _Ary(ch,_Head,NULL);
  _Head->prev = Node;
  _Head = Node;
  _Index++;
}

char Deque::RemoveL()
{
  if (IsEmpty()) { _Error('R'); return false; }
  char tch;
  _Ary * Node;
  Node = _Head;
  tch = Node->ch;
  _Head = Node->next;
  _Head->prev = NULL;
  delete Node;
  _Index--;
  return tch;
}
void Deque::InsertR(char ch)
{
  if (IsFull() == true) { _Error ('I'); return; } 
  _Ary * Node;
  if (IsEmpty()) {
    InsertL(ch);
  }
  else {
    Node = new _Ary(ch,_Tail,_Tail->prev);
    _Tail->prev->next = Node;
    _Tail->prev = Node;
    _Index++;
  }
}

char Deque::RemoveR()
{
  if (IsEmpty()) { _Error('R'); return false; }
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
    _Index--;
    return tch; }
}

void Deque::Size(int i)
{
  _Empty();
  _Index = 0;
  _MaxSize = (i);
}

bool Deque::IsEmpty()
{
  return (_Head == _Tail);
}

bool Deque::IsFull()
{
  if (_Index == _MaxSize) { return true;
  } else { return false; }
}

void  Deque::Debug()
{
  cout << endl;
  for (_Ary *loop = _Head; loop!=_Tail; loop = loop->next) {
    cout << loop->ch << "-"; }
  cout << endl;
  cout << "_MaxSize = " << _MaxSize << endl;
  cout << "_Index = " << _Index << endl;
  cout << "_Head = " << _Head << endl;
  cout << "_Tail = " << _Tail << endl;
}

void Deque::_Empty()
{
  _Ary * Node;
  while(!IsEmpty()) {
    Node = _Head;
    _Head = Node->next;
    _Head->prev = NULL;
    delete Node;
  }
  _Index = 0;
}

void Deque::_Error(char er)
{
  cout << "FAIL " << er << endl;
}


