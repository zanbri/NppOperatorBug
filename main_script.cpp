////
//// main_script.cpp
//// 

///
/// The standard include files
///
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>

///
/// The include files for CUDA
///
#include <cuda_runtime.h>
#include <helper_functions.h>
#include <helper_cuda.h>

///
/// The include files for image filtering
///
#include "class1.h"
#include "class2.h"

///
/// The main function
///
int main( int argc, char *argv[] )
{

    //----------------------------------------------------------------------

    //
    // Allocate memory for frame
    //
    const int srcRows = 100;
    const int srcCols = 100;
    const int srcStep = 3 * srcCols;

    const unsigned int srcFootprint = srcStep * srcRows;
    uint8_t *d_iImage = nullptr;
    checkCudaErrors( cudaMalloc( (void**)&d_iImage, srcFootprint ) );

    //
    // Allocate memory for mean values
    //
    double *d_chMeans = nullptr;
    checkCudaErrors( cudaMalloc( (void**)&d_chMeans, 3 * sizeof(double) ) );


    //------------------------------------------------------------------

    //
    // Load filters, set device pointers and run
    //
    Class1<float> class1;
    class1.setMemPointers( d_iImage, d_chMeans );
    class1.runGPU( srcStep, srcCols, srcRows );

    Class2<float> class2;
    class2.setMemPointers( d_iImage, d_chMeans );
    class2.runGPU( srcStep, srcCols, srcRows );

    //----------------------------------------------------------------------

    //
    // Free allocated memory
    //
    cudaFree(d_iImage);
    cudaFree(d_chMeans);

    return 0;

}

