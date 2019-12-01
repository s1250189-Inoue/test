//test_RPN.cpp
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include "RPN.h"

int main(){
    float Ans;
    std::string s1 = "1 2 + 8 + 4 - -2 + 8 * 4 /";

    std::cout << s1 << std::endl;
    Ans = eval(s1);
    std::cout << "Ans: " << Ans << std::endl;

    return 0;
}