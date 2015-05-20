/*
 * Aditya Dhulipala
 * MediaQueires
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "Frame.h"
#include "SceneDetector.cpp"

using namespace std;

cv::Mat src; cv::Mat dst;
char window_name1[] = "Unprocessed Frame";
char window_name2[] = "Processed Frame";

void testMyImage();

void testSceneDetector();

int main( int argc, char** argv )
{
    /// Load the source image
    src = cv::imread( "../../Resources/fruits.jpg", 1 );

    testMyImage();
    testSceneDetector();

    //cv::namedWindow( window_name1, cv::WINDOW_AUTOSIZE );
    //imshow("Unprocessed Frame",src);

    dst = src.clone();
    GaussianBlur( src, dst, cv::Size( 15, 15 ), 0, 0 );

    //cv::namedWindow( window_name2, cv::WINDOW_AUTOSIZE );
    //imshow("Processed Frame",dst);

    cv::waitKey();
    return 0;
}

void testSceneDetector() {
    // setup
    Frame img1, img2;
    int width = 352;
    int height = 288;
    string s1 = "../../Resources/StarCraft179.rgb";
    string s2 = "../../Resources/StarCraft178.rgb";
    img1.setWidth(width);
    img1.setHeight(height);
    img2.setWidth(width);
    img2.setHeight(height);
    img1.setImagePath(s1.c_str());
    img2.setImagePath(s2.c_str());
    img1.ReadImage();
    img2.ReadImage();

    // test
    string suffix = " for " + s1.substr(16) + " & " + s2.substr(16);
    cout << "ECR = " << computeECR(&img1, &img2) << suffix << endl;
    imshow(s1.substr(16) + " f1", img1.getMatData());
    imshow(s2.substr(16) + " f2", img2.getMatData());

}


void testMyImage() {
    Frame image;
    image.setHeight(288);
    image.setWidth(352);
    image.setImagePath("../../Resources/StarCraft180.rgb");
    image.ReadImage();

    char *img;
    img = image.getImageData();

    std::cout << "Hello from testMyImage()" << std::endl;

    cv::Mat TempMat = cv::Mat(288, 352, CV_8UC3, img);
    imshow("this is a test",TempMat);

}