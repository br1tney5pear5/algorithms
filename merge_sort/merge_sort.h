#include <tgmath.h>
#include <cstring>
#include <vector>
#include <array>

// unrecursive, memory O(2*n)
template<typename T>
void merge_sort(std::vector<T>& vec){
    size_t buf_i = 0;
    std::array< std::vector<T>, 2 > buf = {std::vector<T>(vec.size()),std::vector<T>(vec.size())};
    std::memcpy((void*)&buf[buf_i][0], (const void*)&vec[0], vec.size() * sizeof(T));

    for(size_t j=0; j < ceil(log2(vec.size())); j++){
        auto& in  = buf[  (buf_i & 1) ];
        auto& out = buf[ !(buf_i & 1) ];

        size_t subarr_sz = pow(2, j);
        size_t safe_sz = floor((double)in.size()/(double)(2*subarr_sz));
        size_t unsafe_residue = in.size() - safe_sz * 2 * subarr_sz;

        for(size_t i=0; i<safe_sz; i++){
            auto  left_it = in.begin()  + (i*2  ) * subarr_sz; size_t right_it_shift = 0;   
            auto right_it = in.begin()  + (i*2+1) * subarr_sz; size_t  left_it_shift = 0;
            auto   out_it = out.begin() + (i*2  ) * subarr_sz;

            for(size_t k=0; k<subarr_sz*2; k++){
                if(right_it_shift >= subarr_sz){
                    for(; k<subarr_sz*2; k++){ *(out_it + k) = *(left_it  +  left_it_shift++); }
                } else if(left_it_shift >= subarr_sz){
                    for(; k<subarr_sz*2; k++){ *(out_it + k) = *(right_it + right_it_shift++); }
                } else {
                    if(*(left_it+left_it_shift) > *(right_it + right_it_shift))
                                            { *(out_it + k) = *(right_it + right_it_shift++); }
                    else                    { *(out_it + k) = *(left_it  +  left_it_shift++); }
                }
            }
        }
        if(unsafe_residue){
            auto  left_it = in.begin()  + (2*safe_sz  ) * subarr_sz; size_t  left_it_shift = 0;
            auto right_it = in.begin()  + (2*safe_sz+1) * subarr_sz; size_t right_it_shift = 0;   
            auto   out_it = out.begin() + (2*safe_sz  ) * subarr_sz;
            
            for(size_t k=0; (out_it+k) <= out.end(); k++){
                if(right_it_shift >= subarr_sz || right_it >= in.end()){
                    for(; (out_it+k) <= out.end(); k++){ *(out_it + k) = *(left_it  +  left_it_shift++); }
                } else if(left_it_shift >= subarr_sz){
                    for(; (out_it+k) <= out.end(); k++){ *(out_it + k) = *(right_it + right_it_shift++); }
                } else {
                    if(*(left_it+left_it_shift) > *(right_it + right_it_shift))
                                            { *(out_it + k) = *(right_it + right_it_shift++); }
                    else                    { *(out_it + k) = *(left_it  +  left_it_shift++); }
                }
            }
        }
        buf_i++;
    }
}
