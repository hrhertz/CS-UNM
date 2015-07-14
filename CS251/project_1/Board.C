/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 1
* 
* Ken Segura
* Userid: ksegura@unm.edu
* 
********************************************************************
* 
* Board.C
*
********************************************************************/

#include <iostream>
#include "Board.h"
#include <cstdlib>
using namespace std;

Board::Board()
{
  _X = 1; _Y = 1; _Blk_Cnt = 1;
}

Board::~Board()
{
}

void Board::Run()
{
  while (_Command_Proc());   // Based on Ackley Ducks.C
}

//  Based on Ackley Ducks.C
bool Board::_Command_Proc()
{
  char c;
  cin >> c;
  if (!cin) _Error(); else {
    if (c=='Q') { cout << "QUIT" << endl; return false; }
  switch (c) {
  case 'A':  _CmdAuthor();    break;
  case 'D':  _CmdDelay();     break;
  case 'I':  _CmdInitBrd();   break;
  case 'B':  _CmdSetBlk();    break;
  case 'R':  _CmdReset();     break;
  case 'P':  _CmdPush();      break;
  default:                    break;
  } }
  return true;
}        


void Board::_CmdAuthor()
{
  cout << "AUTHOR \"Ken Segura\"" << endl;   
}

void Board::_CmdDelay()
{
  int Tmp_Int ;
  cin >> Tmp_Int;
  if (!cin) _Error(); else
    cout << "DELAY " << Tmp_Int << endl; 
}

void Board::_CmdInitBrd()
{
  int _Tmp_X,_Tmp_Y,_Tmp_Blk;
  cin >> _Tmp_X;
  if (!cin) _Error(); else if ((_Tmp_X >= 0) && (_Tmp_X < _MAXW))
    _X = _Tmp_X; else _Error();

  cin >> _Tmp_Y;
  if (!cin) _Error(); else if ((_Tmp_Y >= 0) && (_Tmp_Y < _MAXH))
    _Y = _Tmp_Y; else _Error();

  cin >> _Tmp_Blk;
  if (!cin) _Error(); else if ((_Tmp_Blk >= 0) && (_Tmp_Blk < _MAXBLOCKS))
    _Blk_Cnt = _Tmp_Blk; else _Error();
}

void Board::_CmdSetBlk()
{
  int Tmp_BlkNum,Tmp_X,Tmp_Y;
  bool Tmp_MS;
  cin >> Tmp_BlkNum;
  if (!cin) _Error();
  cin >> Tmp_X;
  if (!cin) _Error();
  cin >> Tmp_Y;
  if (!cin) _Error();
  cin >> Tmp_MS;
  if (!cin) _Error();

  _Blocks[Tmp_BlkNum].SetBlk(Tmp_X,Tmp_Y,Tmp_MS);
}

void Board::_CmdReset()
{
  cout << "RESET " << _X << " " << _Y << endl;
  for (int loop = 0; loop < _Blk_Cnt; loop++)
    {
      cout << "BLOCK " << loop << " " << _Blocks[loop].ReadBlk_X() << " " << _Blocks[loop].ReadBlk_Y() << " " << _Blocks[loop].ReadBlk_MS() << endl;
    }
  
}

void Board::_CmdPush()
{
  int Tmp_Int,Mv_Blk;
  char Tmp_Char,Dir;
  int Tmp_X,Tmp_Y;

  // Read Block number.
  cin >> Tmp_Int;
  if (!cin) _Error(); else if ((Tmp_Int >= 0) && (Tmp_Int <= _Blk_Cnt))
    {
      Mv_Blk = Tmp_Int;
    } else _Error();

  // Read direction.
  cin >> Tmp_Char;
  if (!cin) _Error();
  if ((Tmp_Char == 'E') || (Tmp_Char == 'W') || (Tmp_Char == 'S') || (Tmp_Char == 'N'))
    {
      Dir = Tmp_Char;
    } else _Error();
 
  /////////////////
  // Start Pushing!
  
  cout << "PUSHED " << Mv_Blk << endl;
  
  bool Is_It = 0;
  int Nxt_Blk = 0;
  
  ///////
  // Loop untill a condtion breaks you out.
  // This may not be the best way. but it works for now.

  while (1) {
    

    ////////////////////////
    //Is the block maveable?
    // 
    if (!_Blocks[Mv_Blk].ReadBlk_MS()) { return; }
      
    ////////////////////////    
    // Get X,Y for Block. 
    //
    Tmp_X = _Blocks[Mv_Blk].ReadBlk_X();
    Tmp_Y = _Blocks[Mv_Blk].ReadBlk_Y();

    ////////////////////////
    // Is the block next to a wall?
    // Repeat code, Fix later if time permitts.
    //
    switch (Tmp_Char) {
    case 'E':  if ((Tmp_X+1) >= _X)
      { cout << "HALT " << Mv_Blk << endl; return;}   break;
    case 'W':  if ((Tmp_X-1) < 0)
      { cout << "HALT " << Mv_Blk << endl; return;}   break;
    case 'N':  if ((Tmp_Y-1) < 0)
      { cout << "HALT " << Mv_Blk << endl; return;}   break;
    case 'S':  if ((Tmp_Y+1) >= _Y)
      { cout << "HALT " << Mv_Blk << endl; return;}   break;
    default:   _Error(); break;
    } 
    
    /////////////////////////// 
    // Check all blocks to see if one is E,W,S,N of Mv_Blk.
    //
    Is_It = 0;
    Nxt_Blk = 0;
    for (int loop_1 = 0; loop_1 < _Blk_Cnt; loop_1++)  {
      Is_It = _Blocks[loop_1].Check_Loc(Tmp_X,Tmp_Y,Tmp_Char); 
      if (Is_It) {Nxt_Blk = loop_1;  break; }
    }
    
    ////////////////////////////
    // Is there another Block next to me?
    // If there is transfer vals, if not move This block.
    if (Is_It) { cout << "PUSHED " << Nxt_Blk << endl; 
      cout << "HALT " << Mv_Blk << endl;
      Tmp_X = _Blocks[Nxt_Blk].ReadBlk_X();
      Tmp_Y = _Blocks[Nxt_Blk].ReadBlk_Y();
      Mv_Blk = Nxt_Blk;
    } else { _Blocks[Mv_Blk].Push(Dir);
    cout << "MOVE " << Mv_Blk << " ";
    cout << _Blocks[Mv_Blk].ReadBlk_X() << " ";
    cout << _Blocks[Mv_Blk].ReadBlk_Y() << endl;
    }
   
  } // End_While
 
  return;
  
}

void Board::_Error()
{
  ///////////
  // Error Detected, Bail out!
  cerr << "QUIT" << endl;
  exit(1);
}
