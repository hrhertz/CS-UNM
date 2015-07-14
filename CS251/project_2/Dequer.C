/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 2
* 
* Ken Segura
* Userid: ksegura@unm.edu
* 
********************************************************************
* 
* Dequer.C
*
********************************************************************
*
* You must check the Deque before calling InsertR/L and RemoveR/L.
* Use IsFull() & IsEmpty().
*
*******************************************************************/

#include <iostream>
#include "Dequer.h"

Dequer::Dequer()
{

}

Dequer::~Dequer()
{
 
}

void Dequer::Run()
{
  while (_Command_Proc());
}

bool Dequer::_Command_Proc()
{
  char c;
  cin >> c;
  if (!cin) _Error(); else {
    if (c=='Q') { cout << "QUIT" << endl; return false; }
  switch (c) {
  case 'A':  _CmdAuthor();    break;
  case 'D':  _CmdDelay();     break;
  case 'S':  _CmdSize();      break;
  case 'I':  _CmdInsert();    break;
  case 'R':  _CmdRemove();    break;
  case 'L':  _CmdLoad();      break;
  case 'U':  _CmdUnload();    break;
  case 'C':  _CmdCirculate(); break;
  case 'd':  _CmdDebug();     break;
  default:                    break;
  } }
  return true;

}

void Dequer::_CmdAuthor()
{
  cout << "AUTHOR \"Ken Segura\"" << endl; 
}

void Dequer::_CmdDelay()
{
  int Tmp_Int ;
  cin >> Tmp_Int; if (!cin) _Error();

  if (!cin) _Error(); else
    cout << "DELAY " << Tmp_Int << endl;
}

void Dequer::_CmdSize()
{
  int _Size;
  cin >> _Size; if (!cin) _Error();
  _Deque.Size(_Size);
  cout << "SIZE " << _Size << endl;
}

void Dequer::_CmdInsert()
{
  char _lr, ch;
  cin >> _lr; if (!cin) _Error();
  cin.get(ch); if (!cin) _Error();
  if (_Deque.IsFull() == true) { _Fail('I'); return; }
  if (_lr=='L') { _Deque.InsertL(ch); } else if (_lr=='R') { _Deque.InsertR(ch); }
  else { _Error(); }
  cout << "INSERT " << _lr << ch << endl; 
}

void Dequer::_CmdRemove()
{
  char _lr, ch;
  cin >> _lr; if (!cin) _Error();
  if (_Deque.IsEmpty() == true) { _Fail('R'); return; }
  if (_lr=='L') { _lr = 'L' ; ch = _Deque.RemoveL(); } 
  else if (_lr=='R') { _lr = 'R'; ch = _Deque.RemoveR(); }
  else { _Error(); }
  cout << "REMOVE " << _lr << ch << endl;

}

void Dequer::_CmdLoad()
{
  char ch;     	       	       	    
  while (cin.get(ch) && ch!='\n') 
    if (_Deque.IsFull() == false) { _Deque.InsertR(ch); }
    else { _Fail('C'); }
}

void Dequer::_CmdUnload()
{
  cout << "UNLOAD ";
  while (!_Deque.IsEmpty()) {
    cout << _Deque.RemoveL(); }
  cout << endl;
}

void Dequer::_CmdDebug()
{ _Deque.Debug(); }

void Dequer::_CmdCirculate()
{
  char ch, lr;
  cin >> lr; if (!cin) _Error();
  if (_Deque.IsEmpty() == true) { _Fail('C'); return; }
  if (_Deque.IsFull() == true) { _Fail('C'); return; }
  if (lr == 'R') { ch = _Deque.RemoveR(); _Deque.InsertL(ch); } else
    if (lr == 'L') { ch = _Deque.RemoveL(); _Deque.InsertR(ch); } else
      _Error();
  cout << "CIRCULATE " << lr << ch << endl; 
}

void Dequer::_Error()
{
  ///////////
  // Error Detected, Bail out!
  cout << "QUIT" << endl;
  exit(1);
}

void Dequer::_Fail(char er)
{
  //////////
  // Command Failed
  cout << "FAIL " << er << endl;
}
