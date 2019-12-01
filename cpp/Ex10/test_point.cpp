//test_point.cpp
#include<iostream>
#include<fstream>
#include<unordered_set>

using namespace std;

struct Point {
 int x, y;
};

struct Point_hash {
size_t operator()(const Point& r) const
{
size_t h = 0;
// compute a hash for the record
hash<int> hs;
hash<int> hi;
h = hs(r.x) ^ hi(r.y);
return h;
}
};

struct Point_equal {
bool operator()(const Point& r1,
const Point& r2) const
{
// return true if r1 and r2 are
// equal records
return (r1.x==r2.x) && (r1.y==r2.y);
}
};

int main(void) {
 // define the hash set for storing the point
 unordered_set<Point, Point_hash, Point_equal> table;

 ifstream in("point_list.txt");
 cout << "Reading points from file" << endl;
 while (!in.eof()) {
  int x, y;
  in >> x >> y;

  Point p{x,y};
  table.insert(p);
 }
 cout << "Points read from file. Now enter some query point." << endl;

 while (cin) {
  int x, y;
  cin >> x >> y;
  Point p{x,y};
if(table.find(p) != table.end()){
    cout << "point found" << endl;
}
else{
    cout << "not found" << endl;
}
  // check if p is in the table,
  // if it is print "point found"
  // otherwise print "not found"
 }

}