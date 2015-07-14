/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 2
* 
* Ken Segura
* Userid: ksegura@unm.edu
* 
********************************************************************
* 
* Deque.C
*
********************************************************************/

#include <iostream.h>
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
  cin >> Tmp_Int;
  if (!cin) _Error(); else
    cout << "DELAY " << Tmp_Int << endl;
}

void Dequer::_CmdSize()
{
}

void Dequer::_CmdInsert()
{
}

void Dequer::_CmdRemove()
{
}

void Dequer::_CmdLoad()
{

}

void Dequer::_CmdUnload()
{
}

void Dequer::_Error()
{
  ///////////
  // Error Detected, Bail out!
  cout << "QUIT" << endl;
  exit(1);
}


