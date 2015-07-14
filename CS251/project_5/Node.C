/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 5
*
* Ken Segura
* Userid: ksegura@unm.edu
*
********************************************************************
*
* Node.C
*
*******************************************************************/

#include <iostream.h>
#include <assert.h>       /* for assert() */
#include <ctype.h>        /* for isdigit() */
#include <iomanip.h>      /* for setw() */
#include "Node.h"


Node::Node()
{
  left = NULL;
  right = NULL;
}

Node::Node(char what,Node * l, Node * r)
{
  value = what;
  left = l;
  right = r;
}

Node::~Node() { delete left; delete right; }
  
Node* Node::ParseNUM(istream & in)
{
  if (!isdigit(in.peek())) return NULL;  // Not a NUM
  return new Node(in.get(),NULL,NULL);
}

Node* Node::ParseN(istream & in)
{
  if (in.peek() != 'n') return NULL;     // Not a n 
  return new Node(in.get(),NULL,NULL);
}

Node* Node::ParseW(istream & in)
{
  if (in.peek() != 'w') return NULL;     // Not a w
  char ch = in.get();
  Node * a = ParseE(in);
  if (!a) { delete a; return NULL; }     // Clean Up Return NULL
  return new Node(ch,a,NULL);
}

Node* Node::ParseQ(istream & in)
{
  if (in.peek() != '?') return NULL;     // Not a ?
  char ch = in.get();
  Node * a = ParseE(in);
  if (!a) { delete a; return NULL; }     // Clean Up Return NULL
  return new Node(ch,a,NULL);
}      

Node* Node::ParseV(istream & in)
{
  if (in.peek() != 'v') return NULL;     // Not a v
  char ch = in.get();
  Node * a = ParseE(in);
  if (!a) { delete a; return NULL; }     // Clean Up Return NULL
  return new Node(ch,a,NULL);
}	

Node* Node::ParseD(istream & in)
{
  if (in.peek() != 'd') return NULL;     // Not a d
  char ch = in.get();
  Node * a = ParseE(in);
  if (!a) { delete a; return NULL; }      // Clean Up Return NULL
  Node * b = ParseE(in);
  if (!b) { delete a; delete b; return NULL; }
  return new Node(ch,a,b);
}

Node* Node::ParseP(istream & in) 
{
  if (in.peek() != '.') return NULL;     // Not a .
  char ch = in.get();
  Node * a = ParseE(in);
  if (!a) { delete a; return NULL; }     // Clean Up Return NULL
  Node * b = ParseE(in);
  if (!b) { delete a; delete b; return NULL; }
  return new Node(ch,a,b);
  
}

Node* Node::ParseE(istream & in)
{

  // Eat Any White Space
  while (in.peek() == ' ') { in.get(); }

  Node * l = ParseNUM(in);
  if (l) return l;  // E<-NUM

  Node * m = ParseN(in);
  if (m) return m;  // E<-n

  Node * n = ParseW(in);
  if (n) return n;  // E<-w + E
  
  Node * o = ParseQ(in);
  if (o) return o;  // E<-? + E 

  Node * p = ParseV(in);
  if (p)  return p; // E<-v + E

  Node * q = ParseD(in);
  if (q) return q;  // E<-d + E + E

  Node * s = ParseP(in);
  if (s) return s;  // E<-. + E + E

  return NULL;

}

void Node::Print(ostream & o,int depth) {
  
  if (!left && !right) {   // No kids, must be NUM rule
    o << setw(depth) << "" << value << endl;
    return;
  }
  if (left && !right) {   // Just left kid, must be E->NUM rule
    o << setw(depth) << "" << value << endl;
    left->Print(o,depth+2); // so eval left kid & return result
    return;
  }
  assert(left&&right);   // Else need two kids
  right->Print(o,depth+2);   // Use 'reverse inorder' traversal
  o << setw(depth) << "" << value << endl;
  left->Print(o,depth+2);
  
} 










