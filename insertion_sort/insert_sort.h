#include <vector>

template<typename T>
void insert_sort(std::vector<T>& vec){
    for(size_t i=0; i<vec.size(); i++){
        size_t j = i-1;
        while( j >0 && vec[j] > vec[i]){
            vec[j+1] = vec[j];
            j--;
        }
        vec[j] = vec[i];
    }
}
