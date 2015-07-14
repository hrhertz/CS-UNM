#ifndef DEQUE_H        /* -*- C++ -*- */
#define DEQUE_H

// CS251 Program 2, Spring 2000
// Author: Ken Segura
// Email:  ksegura@unm.edu

class Deque {

public:

  Deque(); 
  Deque(const Deque & f);
  Deque & operator=(const Deque & f);
  ~Deque();

  void InsertL(char c);
  char RemoveL();
  void InsertR(char c);
  char RemoveR();
  void Size(int i);
  bool IsEmpty();
  bool IsFull();
  void Debug();

private:
  
  void _Empty();
  class _Ary {
    
  public:

    _Ary(char ch, _Ary * pn, _Ary * pp);
    ~_Ary();
    _Ary * next;   // Next _Ary
    _Ary * prev;   // Previous Ary

    char ch;        // Data

  private:
    
    _Ary(const _Ary & f);
    _Ary & operator=(const _Ary & f);

  };
  
  _Ary * _Head;
  _Ary * _Tail;

  void _Error(char er);
  int _MaxSize, _Index;  

};


#endif

