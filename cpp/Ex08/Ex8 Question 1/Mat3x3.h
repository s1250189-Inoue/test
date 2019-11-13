#ifndef MAT3X3_H
#define MAT3X3_H

#include <iostream>

class Mat3x3{
    public:
        double mat[3][3];
        Mat3x3();
        Mat3x3(double[3][3]);
        Mat3x3 operator+ (const Mat3x3& other);
        Mat3x3 operator- (const Mat3x3& other);
        Mat3x3 operator* (const Mat3x3& other);
        Mat3x3 operator+= (const Mat3x3& other);
        Mat3x3 operator-= (const Mat3x3& other);
        Mat3x3 operator*= (const Mat3x3& other);
        Mat3x3 operator- ();
        double operator() (const int other1, const int other2);
        bool operator== (const Mat3x3& other);
        friend std::ostream& operator<< (std::ostream& os, const Mat3x3& other);
};

#endif