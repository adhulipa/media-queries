//*****************************************************************************
//
// Frame.cpp : Defines the class operations on images
//
// Author - Aditya Dhulipala - based on starter code by Prof. Parag Havaldar
// Code used by students as starter code to display and modify images
//
//*****************************************************************************

#include "Frame.h"


// Constructor and Desctructors
Frame::Frame()
{
    Data = NULL;
    Width = -1;
    Height = -1;
    ImagePath[0] = 0;
}

Frame::~Frame()
{
    if ( Data )
        delete Data;
}


// Copy constructor
Frame::Frame( Frame *otherImage)
{
    Height = otherImage->Height;
    Width  = otherImage->Width;
    Data   = new char[Width*Height*3];
    strcpy(otherImage->ImagePath, ImagePath );

    for ( int i=0; i<(Height*Width*3); i++ )
    {
        Data[i]	= otherImage->Data[i];
    }


}



// = operator overload
Frame &Frame::operator= (const Frame &otherImage)
{
    Height = otherImage.Height;
    Width  = otherImage.Width;
    Data   = new char[Width*Height*3];
    strcpy( (char *)otherImage.ImagePath, ImagePath );

    for ( int i=0; i<(Height*Width*3); i++ )
    {
        Data[i]	= otherImage.Data[i];
    }

    return *this;

}


// Frame::ReadImage
// Function to read the image given a path
bool Frame::ReadImage()
{

    // Verify ImagePath
    if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
    {
        fprintf(stderr, "Frame or Frame properties not defined");
        fprintf(stderr, "Usage is `Frame.exe Imagefile w h`");
        return false;
    }

    // Create a valid output file pointer
    FILE *IN_FILE;
    IN_FILE = fopen(ImagePath, "rb");
    if ( IN_FILE == NULL )
    {
        fprintf(stderr, "Error Opening File for Reading");
        return false;
    }

    // Create and populate RGB buffers
    int i;
    char *Rbuf = new char[Height*Width];
    char *Gbuf = new char[Height*Width];
    char *Bbuf = new char[Height*Width];

    for (i = 0; i < Width*Height; i ++)
    {
        Rbuf[i] = fgetc(IN_FILE);
    }
    for (i = 0; i < Width*Height; i ++)
    {
        Gbuf[i] = fgetc(IN_FILE);
    }
    for (i = 0; i < Width*Height; i ++)
    {
        Bbuf[i] = fgetc(IN_FILE);
    }

    // Allocate Data structure and copy
    Data = new char[Width*Height*3];
    for (i = 0; i < Height*Width; i++)
    {
        Data[3*i]	= Bbuf[i];
        Data[3*i+1]	= Gbuf[i];
        Data[3*i+2]	= Rbuf[i];
    }

    // Clean up and return
    delete Rbuf;
    delete Gbuf;
    delete Bbuf;
    fclose(IN_FILE);

    return true;

}



// Frame functions defined here
bool Frame::WriteImage()
{
    // Verify ImagePath
    // Verify ImagePath
    if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
    {
        fprintf(stderr, "Frame or Frame properties not defined");
        return false;
    }

    // Create a valid output file pointer
    FILE *OUT_FILE;
    OUT_FILE = fopen(ImagePath, "wb");
    if ( OUT_FILE == NULL )
    {
        fprintf(stderr, "Error Opening File for Writing");
        return false;
    }

    // Create and populate RGB buffers
    int i;
    char *Rbuf = new char[Height*Width];
    char *Gbuf = new char[Height*Width];
    char *Bbuf = new char[Height*Width];

    for (i = 0; i < Height*Width; i++)
    {
        Bbuf[i] = Data[3*i];
        Gbuf[i] = Data[3*i+1];
        Rbuf[i] = Data[3*i+2];
    }


    // Write data to file
    for (i = 0; i < Width*Height; i ++)
    {
        fputc(Rbuf[i], OUT_FILE);
    }
    for (i = 0; i < Width*Height; i ++)
    {
        fputc(Gbuf[i], OUT_FILE);
    }
    for (i = 0; i < Width*Height; i ++)
    {
        fputc(Bbuf[i], OUT_FILE);
    }

    // Clean up and return
    delete Rbuf;
    delete Gbuf;
    delete Bbuf;
    fclose(OUT_FILE);

    return true;

}




// Here is where you would place your code to modify an image
// eg Filtering, Transformation, Cropping, etc.
bool Frame::Modify()
{

    // TO DO by student

    // sample operation
    for ( int i=0; i<Width*Height; i++ )
    {
        Data[3*i] = 0;
        Data[3*i+1] = 0;

    }

    return false;
}