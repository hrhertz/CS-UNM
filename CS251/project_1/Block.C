/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 1
* 
* Ken Segura
* Userid: ksegura@unm.edu
* 
********************************************************************
* 
* Block.C
* 
*********************************************************************/

#include <iostream>
#include "Block.h"
#include "Board.h"
using namespace std;

Block::Block()
{
  _Y = 0; _X = 0; _MS = 1;
}

Block::~Block()
{

}

bool Block::At(int x,int y)
{
  
  if ((x == _X) && (y == _Y))
    return true;
  return false;
}

bool Block::Check_Loc(int X, int Y, char Dir)
{

  switch (Dir) {
  case 'E':  if ((X == (_X-1)) && (Y==_Y)) {return true;}   break;
  case 'W':  if ((X == (_X+1)) && (Y==_Y)) {return true;}   break;
  case 'N':  if ((Y == (_Y+1)) && (X==_X)) {return true;}   break;
  case 'S':  if ((Y == (_Y-1)) && (X==_X)) {return true;}   break;
  default:           break;
  } 

return false;
}

void Block::Push(char Dir)
{
  
  switch (Dir) {
  case 'E':  _X++; break;
  case 'W':  _X--; break;
  case 'N':  _Y--; break;
  case 'S':  _Y++; break;
  default:         break;
  }
  
}

void Block::SetBlk(int X, int Y, bool MS)
{ 
  _X = X;
  _Y = Y;
  _MS = MS;
}

int Block::ReadBlk_Y()
{
  return _Y;
}

int Block::ReadBlk_X()
{
  return _X;
}

bool Block::ReadBlk_MS()
{
  return _MS;
}

