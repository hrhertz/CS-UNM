#ifndef Bignum_H
#define Bignum_H 

/**********************************
* CS 251 Spring 2000, Program 3
*
* Ken Segura
* Userid: ksegura
*
***********************************
*
* Bignum.h
*
************************************/

#include <iostream.h>

class Bignum
{

 public:

  Bignum();
  Bignum(const Bignum &i);
  Bignum(int n);
  Bignum(const char * p);
  ~Bignum();

  Bignum Add(Bignum BigInt);
  Bignum Subtract(Bignum BigInt);

  Bignum &operator=(const Bignum &i);
  Bignum &operator=(const int n);
  Bignum &operator=(const char * p);
  Bignum &operator+=(const Bignum &i);
  Bignum &operator-=(const Bignum &i);
  Bignum operator+(const Bignum &b) const;
  Bignum operator-(const Bignum &b) const;
  bool operator==(const Bignum &b) const;
  bool operator!=(const Bignum &b) const;
  bool operator<(const Bignum &b) const;
  bool operator<=(const Bignum &b) const;
  bool operator>(const Bignum &b) const;
  bool operator>=(const Bignum &b) const;

  friend ostream & operator<<(ostream &, const Bignum &);
  friend istream & operator>>(istream &, Bignum &);


 private:

  ///////////
  //

  // CS251 Program 2 (Deque), Spring 2000
  // Author: Ken Segura
  // Email:  ksegura@unm.edu 

  class _Deque {

  public:

    _Deque();
    ~_Deque();

    void Debug() const;
  
    ////////////////////////////////////////
    //Returns a pointer to an array of ints. 
    //First int is size/sign.
    int * Read_Deque() const; 
    ////////////////////////////////////////

    void InsertL(int i);     // Insert from Left.   (For cin.get)
    int  RemoveL();          // Remove from Left.   (Not used)
    void InsertR(int i);     // Insert from Right.  (For add/sub)
    int  RemoveR();          // Remove from right.  (Not used)

    bool IsEmpty() const;    // Is _Deque empty?
    void Empty();            // Empty _Deque!
    
    class _Ary {

    public:

      _Ary(int ti, _Ary * pn, _Ary * pp);
      ~_Ary();

      _Ary * next;   // Next _Ary
      _Ary * prev;   // Previous Ary

      int i;        // Integer Number

    private:

      _Ary(const _Ary & f);
      _Ary & operator=(const _Ary & f);
      
    };

  private:   

    _Deque(const _Deque & f);
    _Deque &operator=(const _Deque &f);

    _Ary * _Head;
    _Ary * _Tail;

    bool Sign;       // 0 = Pos / 1 = Neg
    int Exp;         // Exponent

  };                          
  
  //
  //////////
  
  _Deque _BigInt;
  
};

#endif



