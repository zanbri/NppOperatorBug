////
//// class1.cpp
////

#include "class1.h"

///
/// Set pointers to memory required for GPU function
///
template <typename T>
void Class1<T>::setMemPointers(
        uint8_t *iImage,
        double *chMeans )
{

    d_iImage = iImage;
    d_chMeans = chMeans;

}

////
//// Explicit instantiation for the template class 
////
template class Class1<float>;

