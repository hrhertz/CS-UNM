#ifndef DEQUE_H        /* -*- C++ -*- */
#define DEQUE_H

// CS251 Program 4, Spring 2000
// Author: Ken Segura
// Email:  ksegura@unm.edu

template <class T>
class Deque {

public:

  Deque(); 
  Deque(const Deque & f);
  Deque & operator=(const Deque & f);
  ~Deque();

  void InsertL(T c);
  T RemoveL();
  void InsertR(T c);
  T RemoveR();
  void Size(int i);
  bool IsEmpty();
  bool IsFull();
  void Debug();

private:
  
  void _Empty();
  class _Ary {
    
  public:

    _Ary(T ch, _Ary * pn, _Ary * pp);
    ~_Ary();
    _Ary * next;   // Next _Ary
    _Ary * prev;   // Previous Ary

    T ch;        // Data

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

