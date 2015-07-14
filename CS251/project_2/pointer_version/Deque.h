#ifndef DEQUE_H        /* -*- C++ -*- */
#define DEQUE_H

// CS251 Program 2, Spring 2000
// Author: Ken Segura
// Email:  ksegura@unm.edu

class Deque {
public:
  Deque(); 
  Deque(const Deque &n);
  Deque & operator=(const Deque &c);
  ~Deque();
    
private:
  
  class _Elt {            
  public:     	   	  
    _Elt(int i, _Elt * p); 
    ~_Elt();	      
    int data;		  
    _Elt *next;
    _Elt *prevs; 	  
  };			  
  
  _Elt * _head;
  
  bool _Empty;
  int _count;

  bool _InsertL(char);
  char _RemoveL();
  bool _InsertR(char);
  char _RemoveR();
  bool _IsEmpty();
  bool _IsFull();
};

#endif
