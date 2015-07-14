// CS251 Program 2, Spring 2000
// Ken Segura
// ksegura@unm.edu

#include <iostream.h>
#include "Deque.h"

Deque::Deque()
{
  _head = NULL;
  
}

Deque::Deque(const Deque &n)
{

  _head = NULL;
  *this = n;
  
}


Deque &Deque::operator=(const Deque &c)
{

  /*

  // FIX_ME_!!!!!!!!!!!
  //
  // Deep copy. Use Recursion.

  if (this==&i) return *this;   	   
  
  //Empty();   			   
  Deque temp;   
  for (_Elt * p = i._Left; p; p = p->next) 
  temp._Insert(p->data);                  
  while (!temp._IsEmpty()) {    		   
    int item = temp._Remove();  		   
    Insert(item);       		   
  }		
  
  */

  return *this;

  //
  /////////////////////////

}

Deque::~Deque()
{

}


bool  Deque::_InsertL(char c)
{

  return true;
}

char Deque::_RemoveL()
{

  return '5';
}

bool  Deque::_InsertR(char c)
{
  return true;
}

char Deque::_RemoveR()
{

  return '5';
}

bool Deque::_IsEmpty()
{

  return false;
}

bool Deque::_IsFull()
{

  return false;
}
