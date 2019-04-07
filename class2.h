#ifndef CLASS2_H
#define CLASS2_H

///
/// The standard include files
///
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

//
// A ica_mask filter class
//
template <typename T>
class Class2 {

  private:
    //
    // Declare objects to be stored on device
    //
    uint8_t *d_iImage = nullptr;
    double *d_chMeans = nullptr;
    
  public:
    //
    // Set memory pointers
    //
    void setMemPointers( uint8_t *iImage, double *chMeans );

    //
    // Perform filtering
    //
    int runGPU( const int srcStep, const int srcCols, const int srcRows ) const;

};

#endif // CLASS2_H


