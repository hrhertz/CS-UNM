#ifndef NODE_H
#define NODE_H

// CS251 Program 5, Spring 2000
// Author: Ken Segura
// Email:  ksegura@unm.edu

#include <iostream.h>

class Node
{

 public:

  Node();
  Node(char num,Node *l,Node *r);
  ~Node();

  static Node * ParseNUM(istream &in);
  static Node * ParseE(istream &in);
  static Node * ParseN(istream &in);
  static Node * ParseW(istream &in);
  static Node * ParseQ(istream &in);
  static Node * ParseV(istream &in);
  static Node * ParseD(istream &in);
  static Node * ParseP(istream &in);

  void Print(ostream & o,int depth);

 private:

  char value;
  Node *right;
  Node *left;

  Node(const Node & f) { exit(1); }
  Node & operator=(const Node & f) { exit(1); }

};

#endif
