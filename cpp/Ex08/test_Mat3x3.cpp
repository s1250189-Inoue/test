//test_Mat3x3.cpp
#include <iostream>
#include <cassert>
#include "Mat3x3.h"

using namespace std;

int main(void) {
 Mat3x3 A; // A = I
 double coefficients[3][3] = {{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}};
 Mat3x3 B(coefficients);

 Mat3x3 C = A * B;
 assert(C == B);

 C += B;
 C -= A;
 assert(C(0,0) == 1.0);
 assert(C(1,1) == 9.0);
 assert(C(2,2) == 17.0);

 Mat3x3 D = -A;
 assert(D(0,0) == -1.0);
 assert(D(1,1) == -1.0);
 assert(D(2,2) == -1.0);

 cout << "Tests passed" << endl;

 return 0;
}