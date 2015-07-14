#ifndef LABEL_H         /* -*- C++ -*- */
#define LABEL_H 

// CS251 Program 4, Spring 2000
// Author: Ken Segura
// Email:  ksegura@unm.edu 

#include <iostream.h>

class Label {
  
 public:
  
  Label();
  Label(int len); // ctor w/label length len
  Label(const Label &d);
  Label & operator=(const Label & d);
  ~Label();
  

  void InsertL(char c);
  char RemoveL();
  void InsertR(char c);
  char RemoveR();
  bool IsEmpty() const;
  void _Empty();   
  char * Read_Label() const;

  friend ostream & operator<<(ostream & os,const Label & d);
  friend istream & operator>>(istream & in,Label & d);
  
private:

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
  
};

#endif 
