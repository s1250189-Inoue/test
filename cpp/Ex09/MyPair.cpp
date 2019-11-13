#include <string>
#include <iostream>
#include "MyPair.h"

using namespace std;

int main(void) {
  MyPair<string, int> apair("one", 1);

  cout << "Pair: " << apair.first
    << " " << apair.second << endl;

  return 0;
}
