#include<string>

#ifndef MYPAIR_H
#define MYPAIR_H

template <typename T1,typename T2>
class MyPair{
    public:
    T1 first;
    T2 second;

    // Constructors:
    MyPair(const T1& first,const T2& second){
        this->first = first;
        this->second = second;
    }
};

#endif