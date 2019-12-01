//sort.cpp
#include<iostream>
#include<vector>

template<class Ran>
void sort(Ran begin,Ran end){
    int size = end - begin;
    for(int i = 0; i < size - 1; i++){
        for(int j =1 ; j < size - i; j++){
            if(begin[j-1] > begin[j]){
                std::swap(begin[j-1],begin[j]);
            }
        }
    }
}

int main(){
    std::vector<int> v = {4, 3, 6, 1, 5, 2};
    sort(v.begin(),v.end());
    for(auto itr = v.begin(); itr != v.end(); ++itr) {
        std::cout << *itr << "\n";
    }
    return 0;
}
