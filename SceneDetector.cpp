//
// Created by Aditya Dhulipala on 5/17/15.
//

#include <opencv2/core/core.hpp>
#include <opencv2/gpu/gpu.hpp>
#include "Frame.h"

void computeECR(Frame *f1, Frame *f2) {

    // Step 1 - get mats
    Mat m1 = f1->getMatData();
    Mat m2 = f2->getMatData();

    // Step 2 - do bilateralFilter() on mats

    // Step 3 - do Canny() and dilate()

    // Step 4 - compute entering and exiting pixels

    // Step 5 - Compute Edge-Change ratio form above data

}