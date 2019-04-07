////
//// class2.cpp
////

#include "class2.h"

///
/// Set pointers to memory required for GPU function
///
template <typename T>
void Class2<T>::setMemPointers(
        uint8_t *iImage,
        double *chMeans )
{

    d_iImage = iImage;
    d_chMeans = chMeans;

}

////
//// Explicit instantiation for the template class 
////
template class Class2<float>;

