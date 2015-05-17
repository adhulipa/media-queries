//*****************************************************************************
//
// Image.h : Defines the class operations on images
//
// Author - Aditya Dhulipala - based on starter code by Prof. Parag Havaldar
// Main Image class structure
//
//*****************************************************************************

// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/core/core.hpp>

using namespace cv;

// Class structure of Image
// Use to encapsulate an RGB image
class Image {

private:
    int Width;                    // Width of Image
    int Height;                    // Height of Image
    char ImagePath[100];    // Image location
    char *Data;                    // RGB data of the image
    Mat MatData;

public:
    // Constructor
    Image();

    // Copy Constructor
    Image(Image *otherImage);

    // Destructor
    ~Image();

    // operator overload
    Image &operator=(const Image &otherImage);

    // Reader & Writer functions
    void setWidth(const int w) { Width = w; };
    void setHeight(const int h) { Height = h; };
    void setImageData(const char *img) { Data = (char *) img; };
    void setImagePath(const char *path) { strcpy(ImagePath, path); }
    void setMatData(const Mat data) { MatData = data; }

    int getWidth() { return Width; };
    int getHeight() { return Height; };
    char *getImageData() { return Data; };
    char *getImagePath() { return ImagePath; }
    Mat getMatData() { return MatData; }

    // Input Output operations
    bool ReadImage();
    bool WriteImage();

    // Modifications
    bool Modify();

};

