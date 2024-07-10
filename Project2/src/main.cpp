#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "Image.cpp" // My compiler is fucked up somehow and including this is the only way this works
using namespace std;

unsigned char Multiply(unsigned char topLayer, unsigned char bottomLayer) {
    float result = ((float)topLayer/255 * (float)bottomLayer/255) * 255 + 0.5f;
    return (char)result;
}
// 1 − [(1 − NP1) · (1 − NP2)]
unsigned char Screen(unsigned char topLayer, unsigned char bottomLayer) {
    float result = (1 - (( (1 - (float)topLayer/255) * (1 - (float)bottomLayer/255) ))) * 255 + 0.5f;
    return (char)result;
}
unsigned char Subtract(unsigned char topLayer, unsigned char bottomLayer) {
    int result = (int)topLayer - (int)bottomLayer;
    if (result < 0) {
        result = 0;
    }
    if (result > 255) {
        result = 255;
    }
    return (char)result;
}
unsigned char Addition(unsigned char topLayer, unsigned char bottomLayer) {
    int result = (int)topLayer + (int)bottomLayer;
    if (result > 255) {
        result = 255;
    }
    return (char)result;
}
// NP2 ≤ 0.5 : 2 · NP1 · NP2
// NP2 > 0.5 : 1 − [2 · (1 − NP1) · (1 − NP2)]
unsigned char Overlay(unsigned char topLayer, unsigned char bottomLayer) {
    float NP1 = (float)topLayer/255;
    float NP2 = (float)bottomLayer/255;
    float result;
    if (NP2 <= 0.5) {
        result = (2 * NP1 * NP2) * 255 + 0.5f;
    }
    else {
        result = (1 - ( 2 * (1 - NP1) * (1 - NP2) )) * 255 + 0.5f;
    }
    return (char)result;
}

int main() {

    /* Task 1:
    * Use the Multiply blending mode to combine layer1.tga (top layer) with pattern1.tga (bottom layer).
    */
    Image layer1;
    Image pattern1;
    layer1.read("input/layer1.tga");
    pattern1.read("input/pattern1.tga");
    for (int i = 0; i < layer1.imgData.size(); i++) {
        layer1.imgData[i].B = Multiply(layer1.imgData[i].B, pattern1.imgData[i].B);
        layer1.imgData[i].G = Multiply(layer1.imgData[i].G, pattern1.imgData[i].G);
        layer1.imgData[i].R = Multiply(layer1.imgData[i].R, pattern1.imgData[i].R);
    }
    layer1.write("output/part1.tga");

    /* Task 2:
    * Use the Subtract blending mode to combine layer2.tga (bottom layer) with car.tga (top layer).
    */
    Image layer2;
    Image car;
    layer2.read("input/layer2.tga");
    car.read("input/car.tga");
    for (int i = 0; i < car.imgData.size(); i++) {
        car.imgData[i].B = Subtract(car.imgData[i].B, layer2.imgData[i].B);
        car.imgData[i].G = Subtract(car.imgData[i].G, layer2.imgData[i].G);
        car.imgData[i].R = Subtract(car.imgData[i].R, layer2.imgData[i].R);
    }
    car.write("output/part2.tga");

    /* Task 3:
    * Use the Multiply blending mode to combine layer1.tga with pattern2.tga, and store the
    results temporarily, in memory (aka, don’t write this to a file somewhere, just store the pixel
    values somewhere in your program). Load the image text.tga and, using that as the bottom
    layer, combine it with the previous results of layer1/pattern2 using the Screen blending mode.
    */
    Image layer1B;
    Image pattern2;
    Image text;
    layer1B.read("input/layer1.tga");
    pattern2.read("input/pattern2.tga");
    text.read("input/text.tga");
    for (int i = 0; i < layer1B.imgData.size(); i++) {
        layer1B.imgData[i].B = Multiply(layer1B.imgData[i].B, pattern2.imgData[i].B);
        layer1B.imgData[i].G = Multiply(layer1B.imgData[i].G, pattern2.imgData[i].G);
        layer1B.imgData[i].R = Multiply(layer1B.imgData[i].R, pattern2.imgData[i].R);
    }
    for (int i = 0; i < layer1B.imgData.size(); i++) {
        layer1B.imgData[i].B = Screen(layer1B.imgData[i].B, text.imgData[i].B);
        layer1B.imgData[i].G = Screen(layer1B.imgData[i].G, text.imgData[i].G);
        layer1B.imgData[i].R = Screen(layer1B.imgData[i].R, text.imgData[i].R);
    }
    layer1B.write("output/part3.tga");

    /* Task 4:
    * Multiply layer2.tga with circles.tga, and store it. Load pattern2.tga and, using that
    as the bottom layer, combine it with the previous result using the Subtract blending mode
    */
    Image layer2B;
    Image circles;
    Image pattern2B;
    layer2B.read("input/layer2.tga");
    circles.read("input/circles.tga");
    for (int i = 0; i < layer2B.imgData.size(); i++) {
        layer2B.imgData[i].B = Multiply(layer2B.imgData[i].B, circles.imgData[i].B);
        layer2B.imgData[i].G = Multiply(layer2B.imgData[i].G, circles.imgData[i].G);
        layer2B.imgData[i].R = Multiply(layer2B.imgData[i].R, circles.imgData[i].R);
    }
    for (int i = 0; i < layer2B.imgData.size(); i++) {
        layer2B.imgData[i].B = Subtract(layer2B.imgData[i].B, pattern2.imgData[i].B);
        layer2B.imgData[i].G = Subtract(layer2B.imgData[i].G, pattern2.imgData[i].G);
        layer2B.imgData[i].R = Subtract(layer2B.imgData[i].R, pattern2.imgData[i].R);
    }
    layer2B.write("output/part4.tga");

    /* Task 5:
    * Combine layer1.tga (as the top layer) with pattern1.tga using the Overlay blending mode.
    */
    Image layer1C;
    layer1C.read("input/layer1.tga");
    for (int i = 0; i < layer1C.imgData.size(); i++) {
        layer1C.imgData[i].B = Overlay(layer1C.imgData[i].B, pattern1.imgData[i].B);
        layer1C.imgData[i].G = Overlay(layer1C.imgData[i].G, pattern1.imgData[i].G);
        layer1C.imgData[i].R = Overlay(layer1C.imgData[i].R, pattern1.imgData[i].R);
    }
    layer1C.write("output/part5.tga");

    /* Task 6:
    * Load car.tga and add 200 to the green channel.
    */
    Image carB;
    carB.read("input/car.tga");
    for (int i = 0; i < carB.imgData.size(); i++) {
        carB.imgData[i].G = Addition(carB.imgData[i].G, 200);
    }
    carB.write("output/part6.tga");

    /* Task 7:
    * Load car.tga and scale (multiply) the red channel by 4, and the blue channel by 0. This will
    increase the intensity of any red in the image, while negating any blue it may have.
    */
    Image carC;
    carC.read("input/car.tga");
    for (int i = 0; i < carB.imgData.size(); i++) {
        carC.imgData[i].B *= 0;
        if (carC.imgData[i].R * 4 > 255)
            carC.imgData[i].R = 255;
        else
            carC.imgData[i].R *= 4;


    }
    carC.write("output/part7.tga");

    /* Task 8:
    * Load car.tga and write each channel to a separate file: the red channel should be part8_r.tga,
    the green channel should be part8_g.tga, and the blue channel should be part8_b.tga. (Hint:
    If your red channel image appears all red, try writing [Red, Red, Red] instead of [Red, 0, 0] to the
    file—ditto for green and blue!)
    */
    Image part8_r;
    Image part8_g;
    Image part8_b;
    part8_r.read("input/car.tga");
    part8_g.read("input/car.tga");
    part8_b.read("input/car.tga");
    for (int i = 0; i < car.imgData.size(); i++) {
        part8_r.imgData[i].G = part8_r.imgData[i].R;
        part8_r.imgData[i].B = part8_r.imgData[i].R;
        part8_g.imgData[i].R = part8_g.imgData[i].G;
        part8_g.imgData[i].B = part8_g.imgData[i].G;
        part8_b.imgData[i].R = part8_b.imgData[i].B;
        part8_b.imgData[i].G = part8_b.imgData[i].B;
    }
    part8_r.write("output/part8_r.tga");
    part8_g.write("output/part8_g.tga");
    part8_b.write("output/part8_b.tga");

    /* Task 9:
    * Load layer_red.tga, layer_green.tga and layer_blue.tga, and combine the three files
    into one file. The data from layer_red.tga is the red channel of the new image, layer_green is
    green, and layer_blue is blue.
    */
    Image layer_red;
    Image layer_green;
    Image layer_blue;
    layer_red.read("input/layer_red.tga");
    layer_green.read("input/layer_green.tga");
    layer_blue.read("input/layer_blue.tga");
    for (int i = 0; i < layer_red.imgData.size(); i++) {
        layer_red.imgData[i].G = layer_green.imgData[i].G;
        layer_red.imgData[i].B = layer_blue.imgData[i].B;
    }
    layer_red.write("output/part9.tga");

    /* Task 10:
    * Load text2.tga, and rotate it 180 degrees, flipping it upside down. This is easier than you think!
    Try diagramming the data of an image (such as earlier in this document). What would the data
    look like if you flipped it? Now, how to write some code to accomplish that...?
    */
    Image text2;
    Image text2copy;
    text2.read("input/text2.tga");
    text2copy.read("input/text2.tga");
    // width = text2.head.width, height = text.head.height
    for (int i = 0; i < text2.imgData.size(); i++) {
        text2copy.imgData[i] = text2.imgData[text2.imgData.size()-i-1];
    }
    text2copy.write("output/part10.tga");
}
