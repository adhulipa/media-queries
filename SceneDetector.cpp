//
// Created by Aditya Dhulipala on 5/17/15.
//

#pragma once

#include "Frame.h"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/gpu/gpu.hpp>


/*
 * ECR Computation
 * perorms pretty well
 * Could be better - exploit high data independence in problem
 * -- performs in 138ms for test scenes StarCraft 178 & 179
 */
double computeECR(Frame *f1, Frame *f2) {

    auto start = std::chrono::steady_clock::now();

    // Step 1 - get mats
    Mat m1 = f1->getMatData();
    Mat m2 = f2->getMatData();
    //std::cout << m1.size();

    // Step 2 - do bilateralFilter() on mats
    Mat b1, b2;
    bilateralFilter(m1, b1, -1, 50, 7); // params based on gpu talk - http://on-demand.gputechconf.com/gtc/2013/webinar/opencv-gtc-express-shalini-gupta.pdf
    bilateralFilter(m2, b2, -1, 50, 7); // params based on gpu talk - http://on-demand.gputechconf.com/gtc/2013/webinar/opencv-gtc-express-shalini-gupta.pdf

    // Step 3 - do Canny() and dilate()
    Mat ef1, ef2;
    Canny(b1, ef1, 100, 1);
    Canny(b2, ef2, 100, 1);

    int dilation_size = 6;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
    Mat df1, df2;
    dilate(ef1, df1, element);
    dilate(ef2, df2, element);

    // Step 4 - Compute inverted frame
    Mat if1, if2;
    bitwise_not(df1, if1);
    bitwise_not(df2, if2);

    // Step 5 - compute entering and exiting pixels
    Mat entrPxls, exitPxls;
    bitwise_and(ef1, if2, exitPxls);
    bitwise_and(ef2, if1, entrPxls);

    // Step 6 - Compute Edge-Change ratio form above data
    double x_out = sum(exitPxls)[0];
    double x_in = sum(entrPxls)[0];
    double rho1 = sum(ef2)[0];
    double rho2 = sum(ef1)[0];

    double ecr = fmax(x_in/rho2, x_out/rho1);

    auto end = std::chrono::steady_clock::now();

    auto diff = end - start;

    std::cout << " Finished in " << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()<< "ms" << std::endl;


    return ecr;

}

/*
 * Gpu based ECR computation
 * Very poor utilization.
 * Performs worse than serial computation
 * -- 650ms on test scenes StarCraft178 & 179
 */
double computeECRGpu(Frame *f1, Frame *f2) {

    auto start = std::chrono::steady_clock::now();

    // Step 1 - get mats
    Mat m1 = f1->getMatData();
    Mat m2 = f2->getMatData();
    // Convert to Gpu::Mat
    gpu::GpuMat d_m1(m1);
    gpu::GpuMat d_m2(m2);

    // Step 2 - do bilateralFilter() on mats
    gpu::GpuMat d_b1, d_b2;
    gpu::bilateralFilter(d_m1, d_b1, -1, 50, 7); // params based on gpu talk - http://on-demand.gputechconf.com/gtc/2013/webinar/opencv-gtc-express-shalini-gupta.pdf
    gpu::bilateralFilter(d_m2, d_b2, -1, 50, 7); // params based on gpu talk - http://on-demand.gputechconf.com/gtc/2013/webinar/opencv-gtc-express-shalini-gupta.pdf

    Mat b1(d_b1), b2(d_b2);
    // Step 3 - do Canny() and dilate()
    Mat ef1, ef2;
    Canny(b1, ef1, 100, 1);
    Canny(b2, ef2, 100, 1);

    int dilation_size = 6;
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
    Mat df1, df2;
    dilate(ef1, df1, element);
    dilate(ef2, df2, element);

    // Step 4 - Compute inverted frame
    Mat if1, if2;
    bitwise_not(df1, if1);
    bitwise_not(df2, if2);

    // Step 5 - compute entering and exiting pixels
    Mat entrPxls, exitPxls;
    bitwise_and(ef1, if2, exitPxls);
    bitwise_and(ef2, if1, entrPxls);

    // Step 6 - Compute Edge-Change ratio form above data
    double x_out = sum(exitPxls)[0];
    double x_in = sum(entrPxls)[0];
    double rho1 = sum(ef2)[0];
    double rho2 = sum(ef1)[0];

    double ecr = fmax(x_in/rho2, x_out/rho1);

    auto end = std::chrono::steady_clock::now();

    auto diff = end - start;

    std::cout << " Finished in " << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()<< "ms" << std::endl;


    return ecr;

}