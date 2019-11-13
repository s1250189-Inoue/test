// exception.cpp
#include <stdexcept>
#include <cstdio>
#include <iostream>

using namespace std;

class LogFile{
FILE* p;
  public:
  LogFile(const char* n,const char* a){
    p = fopen(n,a);
  if (!p) {
   throw runtime_error("failed to open file");
 }
  }
~LogFile(){fclose(p);}
void write(const char* w){fputs(w,p);}
//operations, e.g. read(),write()
//operators *and -> to make it behave kile a pointer
};

void doSomeComputation() {
 throw runtime_error("failure during doing some computation");
}

void example() {
 LogFile logfile("logfile.txt", "w+");

 // call a function that performs some computation and may throw
 // an exception

try{
     doSomeComputation();
}catch(exception& e){
    throw;
}

 cout << "closing logfile" << endl;
}

int main(void) {
 cout << "Calling example()" << endl;

try{
 example();
}catch(exception& e){
cout << e.what() << endl;
}

 cout << "After calling example()" << endl;
 return 0;
}