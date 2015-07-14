#include <iostream.h>
#include "Bignum.h"

int main()
{

	Bignum testvar;

	cout << "Please enter a Bignum" << endl;

	cin >> testvar;

	cout << testvar << endl;

        cout << "Bignum testvar2 = 913;" << endl;
	Bignum testvar2 = 913;

	cout << testvar2 << endl;

	cout << "testvar = 654;" << endl;
	testvar = 654;

	cout << testvar << endl;

	cout << "testvar2" << endl;
	cout << testvar2 << endl;

	Bignum testvar4;

	cout << "var+var2 " << (testvar+testvar2) << endl;

	testvar4 = testvar + testvar2;
	cout << "testvar4 " << testvar4 << endl;

	testvar = 123;
	testvar2 = 111;
	testvar += testvar;
	cout << "testvar " << testvar << " testvar2 " << testvar2 << endl;
}
