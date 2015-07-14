#ifndef PARSER_H             /* -*- C++ -*- */
#define PARSER_H

// CS251 Program 5, Spring 2000
// Author: Ken Segura
// Email:  ksegura@unm.edu

#include <iostream.h>

class Parser {
  
public:

  Parser(); 
  void Run(istream&,ostream&);

private:

  Parser(const Parser & f) { exit(1); }
  Parser & operator=(const Parser & f) { exit(1); }

};

#endif
