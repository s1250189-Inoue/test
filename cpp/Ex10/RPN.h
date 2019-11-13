#include<iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>

#ifndef RPN_H
#define RPN_N

    float eval(const std::string& e){
        std::stringstream ss(e);
        std::stack<float> st;            //stack
        float number;                      //number
        float a,b;
        std::string str;                 //"+,-,*,/"
        while(!ss.eof()){
            ss >> str;                   //ss -> string
            if(str == "+"){              // "+"
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(a+b);
            }
            else if(str == "-"){          // "-"
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(b-a);
            }
            else if(str == "*"){           // "*"
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(a*b);
            }
            else if(str == "/"){          // "/"
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(b/a);
            }
            else{
                number = atoi(str.c_str());
                st.push(number);
            }
        }
        return st.top();
    }

#endif