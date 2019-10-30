#include<iostream>
#include"Shape2D.h"
#include"Circle.h"
#include"Rectangle.h"
#include"assertFloat.h"
// COMPLETE include the necessary headers here

const float PI = 3.141593f;

int main(void) {
  const int NUM_SHAPES = 2;
  Shape2D* shapes[NUM_SHAPES];
  Point2D center(0.0f, 0.0f);
  shapes[0] = new Circle(center, 1.0f);

  Point2D left_corner(-1.0f, -1.0f);
  shapes[1] = new Rectangle(left_corner, 4.0f, 2.0f);

  for (int i = 0; i < NUM_SHAPES; ++i) {
    float tx = 1.0f;
    float ty = -1.0f;
    shapes[i]->translate(tx, ty);
   }

   assertFloat(shapes[0]->compute_area(), PI);
   assertFloat(shapes[1]->compute_area(), 8.0);

   // COMPLETE free memory for shapes

   return 0;
  }