#include "Image.h"


Image::Image() = default;

void Image::read(const string& inName) {
    //(14) Read in the .tga file
    this->file.open(inName, ios_base::binary);
    //(15) Check if the file is opening
    if (!file.is_open()) {
      return;
    }
    //(16) Read in each element of the .tga file
    file.read((char*) &head.idLength, sizeof(head.idLength));
    file.read((char*) &head.colorMapType, sizeof(head.colorMapType));
    file.read((char*) &head.dataTypeCode, sizeof(head.dataTypeCode));
    file.read((char*) &head.colorMapOrigin, sizeof(head.colorMapOrigin));
    file.read((char*) &head.colorMapLength, sizeof(head.colorMapLength));
    file.read((char*) &head.colorMapDepth, sizeof(head.colorMapDepth));
    file.read((char*) &head.xOrigin, sizeof(head.xOrigin));
    file.read((char*) &head.yOrigin, sizeof(head.yOrigin));
    file.read((char*) &head.width, sizeof(head.width));
    file.read((char*) &head.height, sizeof(head.height));
    file.read((char*) &head.bitsPerPixel, sizeof(head.bitsPerPixel));
    file.read((char*) &head.imageDescriptor, sizeof(head.imageDescriptor));
    
    //(17) Get the image size by multiplying the image height and width
    int imgSize = (int)head.width * (int)head.height;

    //(18) Create a for loop to read in all the pixels
    for (int i = 0; i < imgSize; i++) {
        //(21) Push in each pixel to the pixel vector
        Pixel newPixel;
        file.read((char*) &newPixel.B, sizeof(newPixel.B));
        file.read((char*) &newPixel.G, sizeof(newPixel.G));
        file.read((char*) &newPixel.R, sizeof(newPixel.R));
        imgData.push_back(newPixel);
    }
}

void Image::write(const string& outName) {
    //(22) Create a .tga file
    ofstream outFile(outName, ios_base::binary);
    //(23) Write out each .tga file header element
    outFile.write( &head.idLength, sizeof(head.idLength));
    outFile.write( &head.colorMapType, sizeof(head.colorMapType));
    outFile.write( &head.dataTypeCode, sizeof(head.dataTypeCode));
    outFile.write((char*) &head.colorMapOrigin, sizeof(head.colorMapOrigin));
    outFile.write((char*) &head.colorMapLength, sizeof(head.colorMapLength));
    outFile.write( &head.colorMapDepth, sizeof(head.colorMapDepth));
    outFile.write((char*) &head.xOrigin, sizeof(head.xOrigin));
    outFile.write((char*) &head.yOrigin, sizeof(head.yOrigin));
    outFile.write((char*) &head.width, sizeof(head.width));
    outFile.write((char*) &head.height, sizeof(head.height));
    outFile.write( &head.bitsPerPixel, sizeof(head.bitsPerPixel));
    outFile.write( &head.imageDescriptor, sizeof(head.imageDescriptor));
    //(24) Create a for loop to write out each pixel
    for (int i = 0; i < imgData.size(); i++) {
        //(25) Write out each image pixel
        outFile.write((char*) &imgData[i].B, sizeof(imgData[i].B));
        outFile.write((char*) &imgData[i].G, sizeof(imgData[i].G));
        outFile.write((char*) &imgData[i].R, sizeof(imgData[i].R));
    }
}
