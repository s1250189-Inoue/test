#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;
int main(){
    string s = "1 2 + 8 + 4 - -2 + 8 * 2 /";
    stringstream ss;
    ss << s;
    stack<double> ret;            //stack
    int number;                //number
    double a,b;
    string str;         //"+,-,*,/"
    while(!ss.eof()){
        ss >> str;
        if(str == "+"){
            a = ret.top();
            ret.pop();
            b = ret.top();
            ret.pop();
            ret.push(a+b);
            cout << ret.top() << endl;
        }
        else if(str == "-"){
            a = ret.top();
            ret.pop();
            b = ret.top();
            ret.pop();
            ret.push(b-a);
            cout << ret.top() << endl;
        }
        else if(str == "*"){
            a = ret.top();
            ret.pop();
            b = ret.top();
            ret.pop();
            ret.push(a*b);
            cout << ret.top() << endl;
        }
        else if(str == "/"){
            a = ret.top();
            ret.pop();
            b = ret.top();
            ret.pop();
            ret.push(b/a);
            cout << ret.top() << endl;
        }
        else{
            number = atoi(str.c_str());
            ret.push(number);
            cout << ret.top() << endl;
        }
    }
    return 0;
}