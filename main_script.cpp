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
/// The include files for OpenCV
///
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/videoio.hpp"

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

    ///
    /// Create frame
    ///
    cv::Mat h_iImage( 100, 100, CV_8UC3 );
    cv::randu( h_iImage, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 255) );

    const int srcStep = (int)h_iImage.step;
    const int srcCols = (int)h_iImage.cols;
    const int srcRows = (int)h_iImage.rows;

    //
    // Allocate memory for frame
    //
    const unsigned int imageFootprint = h_iImage.step * h_iImage.rows;
    uint8_t *d_iImage = nullptr;
    checkCudaErrors( cudaMalloc( (void**)&d_iImage, imageFootprint ) );
    checkCudaErrors( cudaMemcpy( d_iImage, h_iImage.data, imageFootprint, cudaMemcpyHostToDevice ) );

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

