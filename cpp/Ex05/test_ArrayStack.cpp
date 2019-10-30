// test_ArrayStack.cpp
#include "ArrayStack.h"

int main(void) {
// Create an instance of ArrayStack named stack1
//   using the default constructor
// Push 1,2,3,4,5 in this stack
ArrayStack stack1;
for(int i = 1;i <= 5; i++){
    stack1.push(i);
}

// Create another instance of ArrayStack named stack2
//   using the other constructor, specify an original size of 5
// Push 1,2,...,10 in this stack
ArrayStack stack2;
for(int i = 1;i <= 10; i++){
    stack2.push(i);
}

return 0;
}