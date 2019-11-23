#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

template<typename A>
float compute_median(A begin,A end){
    int size = end - begin;
    if(size%2 == 1) return (float)begin[size/2];
    else{
        float median = ((float)begin[size/2]+(float)begin[(size/2)+1])/2;
        return median;
    }
}

template<typename B>
void compute_k_closest(B begin,B end,float median,int k){
    Compare comp;
    std::priority_queue<int, std::vector<int>, Compare > q(comp); // compare 2 value by comp(l,r)
    float tmp;
    for(auto itr = begin; itr != end; ++itr) {
        tmp = (float)*itr - median;
        if(tmp >= 0) q.push(tmp);
        else q.push(-1*tmp);
    }
    auto itr = begin;
    while (!q.empty()) {
        std::cout << q.top() << std::endl;
        q.pop();
    }
}

int main(){
    std::vector<int> n = {7,14,10,12,2,11,29,3,4};
    std::sort(n.begin(), n.end());

    // print sorted array
    /*for(auto itr = n.begin(); itr != n.end(); ++itr) {
        std::cout << *itr << "\n";
    }
    */

   // calculate median
   float median = compute_median(n.begin(),n.end());
   std::cout << median << std::endl;

   int k = 3;
   compute_k_closest(n.begin(),n.end(),median,k);
    return 0;
}