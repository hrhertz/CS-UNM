
/****************REQUIRED COMMENT SECTION***************************
* CS 251 Spring 2000, Program 5
*
* Ken Segura
* Userid: ksegura@unm.edu
*
********************************************************************
*
* Parser.C
*
*******************************************************************/
#include <iostream.h>
#include <strstream.h>
#include "Parser.h"
#include "Node.h"

Parser::Parser()
{


}

void Parser::Run(istream&,ostream&)
{
  Node * t;

  while ((t = Node::ParseE(cin))) { // Quit loop on parse error
    t->Print(cout,0);
    delete t;
  }
}

