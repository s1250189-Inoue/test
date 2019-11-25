#ifndef THREAD_H
#define THREAD_H

#include<iostream>
#include<vector>
#include<thread>
#include<functional>
#include<mutex>

std::mutex m;

void split(std::size_t nele,std::size_t nthreads,std::vector<std::size_t> lower,std::vector<std::size_t> higher){

}

// assume that *result has been initialized to 0 in the caller.
void dot_product (const std::vector<double>& v1, const std::vector<double>& v2, double* result) {
  std::size_t len = v1.size();
  double sum = 0;
  for (std::size_t i = 0; i < len; ++i) {
    sum += v1[i] * v2[i];
  }
  *result += sum;
}

void dot_product (const std::vector<double>& v1, const std::vector<double>& v2, double* result, std::size_t lower, std::size_t higher)
{
  double sum = 0;
  for (std::size_t i = lower; i < higher; ++i) {
    sum += v1[i]*v2[i];
  }

  *result += sum;
}


#endif