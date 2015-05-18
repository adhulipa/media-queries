//*****************************************************************************
//
// Frame.h : Defines the class operations on images
//
// Author - Aditya Dhulipala - based on starter code by Prof. Parag Havaldar
// Main Frame class structure
//
//*****************************************************************************

// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <opencv2/core/core.hpp>

using namespace cv;

// Class structure of Frame
// Use to encapsulate an RGB image
class Frame {

private:
    int Width;                    // Width of Frame
    int Height;                    // Height of Frame
    char ImagePath[100];    // Frame location
    char *Data;                    // RGB data of the image
    Mat MatData;

public:
    // Constructor
    Frame();

    // Copy Constructor
    Frame(Frame *otherImage);

    // Destructor
    ~Frame();

    // operator overload
    Frame &operator=(const Frame &otherImage);

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

