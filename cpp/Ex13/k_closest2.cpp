#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<functional>

float median;

template<typename A>
float compute_median(A begin,A end){
    int size = end - begin;
    if(size%2 == 1) return (float)begin[size/2];
    else{
        float median = ((float)begin[size/2]+(float)begin[(size/2)+1])/2;
        return median;
    }
}

auto Compare= [](int a,int b){
    if(((float)a-median)*((float)a-median) > ((float)b-median)*((float)b-median)) return true;
    else return false;
    };

void compute_k_closest(std::vector<int> n, int k){
    std::priority_queue<int, std::vector<int>, decltype(Compare)> que(Compare);
    for(int i = 0; i < n.size(); ++i) {
        que.push(n[i]);
    }
    std::cout << "k-closest numbers to the median are: ";
    for(int i = 0; i < k; ++i) {
        std::cout << que.top() << " ";
        que.pop();
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> n = {7,14,10,12,2,11,29,3,4};
    std::sort(n.begin(),n.end());

    // print sorted array
    /*for(auto itr = n.begin(); itr != n.end(); ++itr) {
        std::cout << *itr << "\n";
    }
    */

   // calculate median
    median = compute_median(n.begin(),n.end());
   std::cout << "median is " << median << std::endl;

   int k = 3;
   compute_k_closest(n,k);
    return 0;
}