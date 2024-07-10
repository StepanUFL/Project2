#pragma once
#ifndef IMAGE_H
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//(1) Declare a Header struct
struct Header {
    //(2) Declare each Header element
    char idLength;

    char colorMapType;

    char dataTypeCode;

    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;

    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};


//(3) Declare a Pixel struct
struct Pixel {
    //(4) Declare each Pixel element
    unsigned char B;
    unsigned char G;
    unsigned char R;
};
//(5) Declare an Image class
class Image {
    //(6) Declare private data member of the Image class
  private:
    //(7) Declare a name
    string name;
    //(8) Declare a stream (ifstream)
    ifstream file;

  public:
    //(9) Declare a header for the Image
    Header head{};
    //(10) Declare a vector of pixels
    vector<Pixel> imgData;

    //(11) Declare an Image constructor
    Image();

    //(12) Declare a read function
    void read(const string& inName);

    //(13) Declare a write function
    void write(const string& outName);
};
#endif // IMAGE_H
