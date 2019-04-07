////
//// The kernel functions for an class1
////

///
/// The include files for class1
///
#include "class1.h"
#include "class1_kernel.h"

//=================================================================================================

///
/// Run main GPU function
///
template <typename T>
int Class1<T>::runGPU( const int srcStep, const int srcCols, const int srcRows ) const
{ 

    NppStatus npp_err;

    //----------------------------------------------------------------------

    ///
    /// Calculate mean values per channel
    ///

    {

        //
        // Set variables needed for NPP functions
        //
        const NppiSize srcSize = { srcCols, srcRows };
        Npp8u * pDeviceBuffer;
        int nBufferSize;

        // Calculate buffer size of scratch buffer needed to calculate sum
        npp_err = nppiMeanGetBufferHostSize_8u_C3R( srcSize, &nBufferSize );

        // Check NPP error status
        if( npp_err != NPP_SUCCESS ) {
        std::cerr << "Error occured during nppiMeanGetBufferHostSize_8u_C3R run: "
              << "( NPP Status: " << npp_err << " ):"
              << __FILE__ << " : " << __LINE__
              << std::endl;
        exit(1);
        }

        // Allocate the scratch buffer 
        cudaMalloc((void **)(&pDeviceBuffer), nBufferSize);

        //
        // Run NPP's mean function
        //
        npp_err = nppiMean_8u_C3R( d_iImage, srcStep, srcSize, pDeviceBuffer, d_chMeans );

        // Check NPP error status
        if( npp_err != NPP_SUCCESS ) {
        std::cerr << "Error occured during nppiMean_8u_C3R run: "
              << "( NPP Status: " << npp_err << " ):"
              << __FILE__ << " : " << __LINE__
              << std::endl;
        exit(1);
        }

        // Free memory for scratch buffer
        cudaFree(pDeviceBuffer);

    }

    //----------------------------------------------------------------------

    return 0;

}

////
//// Explicit instantiation for the template class
////
template class Class1<float>;

