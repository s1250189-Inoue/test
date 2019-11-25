#include<iostream>
#include<vector>
#include<thread>
#include<functional>
#include"thread.h"

// complete: headers ...
// complete: write the function split that computes the lower/higher indices 
// for which each thread will be responsible.
// complete: add dot_product and modify it such that there is no race condition. 

// complete: the main function
int main(void) {
  std::size_t nele = 1000000; // you can modify this to experiment
  std::size_t nthreads = 2; // and this as well, it depends on the number of cores on your machine
  double result = 0;

  std::vector<double> v1(nele);
  // complete: fill v1 with random integers
  for (size_t i = 0; i < nele; ++i) {
    v1[i] = double(rand())/double(RAND_MAX);
  }

  std::vector<double> v2(nele);
  for (size_t i = 0; i < nele; ++i) {
    v2[i] = double(rand())/double(RAND_MAX);
  }

  // complete: split nele into nthreads part
  std::vector<std::size_t> lower;
  std::vector<std::size_t> higher;
  // lower[i] and higher[i] contains the lower and higher indices
  // for which a given thread will compute the dot product
  split(nele, nthreads, lower, higher);

  // complete: start nthreads threads
  // don't forget to pass explicitly a reference to the arrays v1 and v2
  std::vector<std::thread> threads;
  for (std::size_t i=0; i<nthreads; ++i) {
    // start a thread that will compute the dot product between v1 and v2 
    // for indices between lower[i] and higher[i]
  }

  // complete: join the threads with the main thread

  std::cout << "Result: " << result << std::endl;
}