#ifndef BOARD_H         /* -*- C++ -*- */
#define BOARD_H

//Ken Segura
//ksegura@unm.edu

#include <iostream>
#include "Block.h"

class Board {
public:
  Board();
  ~Board();
  void Run();

private:  

  bool _Command_Proc();
  void _CmdAuthor();
  void _CmdDelay();
  void _CmdInitBrd();
  void _CmdSetBlk();
  void _CmdReset();
  void _CmdPush();
  void _Error();

  int _X, _Y, _Blk_Cnt;
  enum {_MAXW = 50, _MAXH = 50, _MAXBLOCKS = 100};
  Block _Blocks[100];
};
#endif
