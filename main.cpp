#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include"image.hpp"

using namespace cv;
using namespace std;

int main()
{
    String imgloc = "C:/Users/NicoVri/Pictures/Hough Images/Legumes.jpg";
    Image image(imgloc);

    //image.TransformGrayScale();

    //image.FiltrageMasque3x3(-1, 0, 1, -2, 0, 2, -1, 0, 1);
    //image.FiltrageMasque3x3(1, 2, 1, 0, 0, 0, -1, -2, -1);
    //image.FiltrageMasque3x3(-1, -1, -1, -1, 8, -1, -1, -1, -1);
    //image.FiltrageMasque3x3(-1, -1, -1, -1, 9, -1, -1, -1, -1);
    /*double i = 0.1111111111111; //1/9
    image.FiltrageMasque3x3(i, i, i, i, i, i, i, i, i);*/

    image.DisplayImage("Image Window");
    //image.ColorChannelInversionBlueRed();
    /*image.DisplayBlueColorFilter();
    image.DisplayGreenColorFilter();
    image.DisplayRedColorFilter();*/
    image.DisplayColorFilters();
}
