
// COMPLETE include the necessary headers here
  #include<cmath>
  #include<cassert>

  inline void assertFloat(float x, float y, float eps=1e-5) {
    assert(std::fabs(x-y) < eps);
  }