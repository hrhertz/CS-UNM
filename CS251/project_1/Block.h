#ifndef BLOCK_H        /* -*- C++ -*- */
#define BLOCK_H

#include <iostream>

class Block {
 public:
  Block ();			// Build a block
  ~Block();
  bool At(int x,int y) ;	// Is this block at (x,y)? 
  bool Check_Loc(int X, int Y, char Dir);
  void Push(const char c) ;	// This block is pushed in direction c
  void SetBlk(int X, int Y, bool MS);  
  int ReadBlk_Y();
  int ReadBlk_X();
  bool ReadBlk_MS();

 private:
  
  int _X, _Y; 
  bool _MS;

};

#endif
