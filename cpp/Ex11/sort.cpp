#include<iostream>
#include<vector>

template<class Ran>
/*void sort(Ran first,Ran last){

}*/

int main(){
    std::vector<int> v = {1, 2, 3, 6, 5, 4};
    sort(v.begin(),v.end());
    return 0;
}
