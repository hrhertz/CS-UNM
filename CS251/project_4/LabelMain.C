#include "LabelMain.h"

// NOTE: This file is made artificially more complicated
//  to test out the value semantics of the Deque contained
//  in your class Dequer!

Dequer<Label> func(Dequer<Label> a)
{      	 	   						  
  Dequer<Label> temp;// default ctor    	       	       	       	  
  temp = a;	    // operator=   				  
  temp.Run();	    // method call				  
  temp = temp;      // operator=
  return temp;	    // copy ctor during return			  
}      	      	    // dtor on temp, dtor on a			  
 	      				      			  
int main()    				      			  
{	      				      			  
  Dequer<Label> d;   // default ctor	      			  
  d = func(d);	    // copy ctor before call, operator= after call
  return 0;    	  			      
}		    // dtor on d       	      
