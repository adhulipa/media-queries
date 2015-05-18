#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Frame.h"
#include <iostream>

cv::Mat src; cv::Mat dst;
char window_name1[] = "Unprocessed Frame";
char window_name2[] = "Processed Frame";

void testMyImage();

int main( int argc, char** argv )
{
    /// Load the source image
    src = cv::imread( "../../Resources/fruits.jpg", 1 );

    testMyImage();

    //cv::namedWindow( window_name1, cv::WINDOW_AUTOSIZE );
    //imshow("Unprocessed Frame",src);

    dst = src.clone();
    GaussianBlur( src, dst, cv::Size( 15, 15 ), 0, 0 );

    //cv::namedWindow( window_name2, cv::WINDOW_AUTOSIZE );
    //imshow("Processed Frame",dst);

    cv::waitKey();
    return 0;
}

void testMyImage() {
    Frame image;
    image.setHeight(288);
    image.setWidth(352);
    image.setImagePath("../../Resources/flowers006.rgb");
    image.ReadImage();

    char *img;
    img = image.getImageData();

    std::cout << "Hello from testMyImage()" << std::endl;
    std::cout << img[0] << std::endl;

    cv::Mat TempMat = cv::Mat(288, 352, CV_8UC3, img);
    imshow("this is a test",TempMat);

}