#ifndef DEQUER_H         /* -*- C++ -*- */
#define DEQUER_H

// CS251 Program 2, Spring 2000
// Author: Ken Segura
// Email:  ksegura@unm.edu

#include <iostream.h>
#include "Deque.h"

class Dequer {
public:
  
  Dequer();			// Once-only dequer inits
  ~Dequer();
  void Run();			// Engine entry point
  
private:

  bool _Command_Proc();
  void _CmdAuthor();
  void _CmdDelay();
  void _CmdSize();
  void _CmdInsert();
  void _CmdRemove();
  void _CmdLoad();
  void _CmdUnload();
  void _Error();


};
#endif
