// stringToInt.cpp
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int stringToInt(const string& input) {
  stringstream instream;
  instream << input;
  int number;
  instream >> number;

  if (instream.fail()) {
    // Error: the input can not be converte
    throw invalid_argument("input can not be converted to an int");
  }

  char left;
  instream >> left;
  if (!instream.fail()) {
    // Error: there are some characters left after the int
    throw invalid_argument("input can not be converted to an int");
  }

return number;

  // everything went fine: returns the int
}


int main(void) {
try{
  string test1 = "11";
  int n = stringToInt(test1);
  cout << n << endl;
  }catch(invalid_argument e){
    cout << e.what() << endl;
  }

try{
  string test2 = "cc11";
  int n = stringToInt(test2);
  cout << n << endl;
}catch(invalid_argument e){
    cout << e.what() << endl;
  }

try{
  string test3 = "11cc";
  int n = stringToInt(test3);
  cout << n << endl;
}catch(invalid_argument e){
    cout << e.what() << endl;
  }

  cout << "Tests passed" << endl;

  return 0;
}
