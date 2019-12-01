//k_closest.cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<functional>

struct Point {
 Point() : x(0.0), y(0.0), z(0.0) {}
 Point(double x, double y, double z) : x(x), y(y), z(z) {}
 double x, y, z;
};

auto Compare= [](Point p1,Point p2){
if(sqrt(p1.x*p1.x+p1.y*p1.y+p1.z*p1.z)<sqrt(p2.x*p2.x+p2.y*p2.y+p2.z*p2.z)) return true;
else false;
};

std::vector<Point> find_k_closest(int k,std::vector<Point> point){
    std::priority_queue<Point, std::vector<Point>, decltype(Compare)> que(Compare);
    for(int i = 0;i < point.size();i++) {
        que.push(point[i]);
    }
    std::vector<Point> another;
    while(!que.empty()){
        another.insert(another.begin(),que.top());
        que.pop();
    }
    std::vector<Point> another2;
    for(int i = 0;i < k;i++){
        another2.push_back(another[i]);
    }
    return another2;
};

int main(void) {
    std::vector<Point> points;
    points.push_back(Point(1.0,2.0,3.0));
    points.push_back(Point(5.0,5.0,5.0));
    points.push_back(Point(0.0,2.0,1.0));
    points.push_back(Point(9.0,2.0,1.0));
    points.push_back(Point(1.0,2.0,1.0));
    points.push_back(Point(2.0,2.0,1.0));

    std::vector<Point> closest = find_k_closest(3, points);
    for (size_t i = 0; i < 3; ++i) {
        std::cout << closest[i].x << "," << closest[i].y << ","
             << closest[i].z << std::endl;
    }

}