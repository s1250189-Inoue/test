#include "Mat3x3.h"
#include <iostream>

Mat3x3::Mat3x3(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            mat[i][j]=0;
            if(i==j)mat[i][j]=1;
        }
    }
};

Mat3x3::Mat3x3(double a[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            mat[i][j]=a[i][j];
        }
    }
};

Mat3x3 Mat3x3::operator+ (const Mat3x3& other){
    Mat3x3 a;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            a.mat[i][j]=this->mat[i][j]+other.mat[i][j];
        }
    }
    return a;
};

Mat3x3 Mat3x3::operator- (const Mat3x3& other){
    Mat3x3 a;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            a.mat[i][j]=this->mat[i][j]-other.mat[i][j];
        }
    }
    return a;
};

Mat3x3 Mat3x3::operator* (const Mat3x3& other){
    Mat3x3 a;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            a.mat[i][j]=0;
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                a.mat[i][j]+=this->mat[i][k]*other.mat[k][j];
            }
        }
    }
    return a;
};

Mat3x3 Mat3x3::operator+= (const Mat3x3& other){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            this->mat[i][j]+=other.mat[i][j];
        }
    }
    return *this;
};

Mat3x3 Mat3x3::operator-= (const Mat3x3& other){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            this->mat[i][j]-=other.mat[i][j];
        }
    }
    return *this;
};

Mat3x3 Mat3x3::operator*= (const Mat3x3& other){
    Mat3x3 a;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                a.mat[i][j]+=this->mat[i][k]*other.mat[k][j];
            }
        }
    }
    return a;
};

Mat3x3 Mat3x3::operator- (){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            this->mat[i][j]*=-1;
        }
    }
    return *this;  
};

double Mat3x3::operator() (const int other1, const int other2){
    return this->mat[other1][other2];
};

bool Mat3x3::operator== (const Mat3x3& other){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(this->mat[i][j]!=other.mat[i][j])return false;
        }
    }
    return true;
};

std::ostream& operator<< (std::ostream& os, const Mat3x3& other){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            os << other.mat[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
};
