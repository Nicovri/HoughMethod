#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include"image.hpp"

using namespace cv;
using namespace std;

int main()
{
    String imgloc = "C:/Users/NicoVri/Pictures/Hough Images/Pieces.png"; // Chemin direct de l'image dans l'ordinateur
    Image image(imgloc);
    image.DisplayImage("Image Window");

    //image.TransformGrayScale();
    //image.FiltrageMasque3x3(-1, 0, 1, -2, 0, 2, -1, 0, 1);
    //image.FiltrageMasque3x3(1, 2, 1, 0, 0, 0, -1, -2, -1);
    //image.FiltrageMasque3x3(-1, -1, -1, -1, 8, -1, -1, -1, -1);
    //image.FiltrageMasque3x3(-1, -1, -1, -1, 9, -1, -1, -1, -1);
    /*double i = 0.1111111111111; //1/9
    image.FiltrageMasque3x3(i, i, i, i, i, i, i, i, i);*/
    //image.DisplayImage("ImageGray Window");
    //image.DisplayOtherImage("Histogram Wondow", image.Histogramme());

    //image.DisplayOtherImage("ColorInversion Window", image.ColorChannelInversionBlueRed());
    //image.DisplayOtherImage("BlueColorFilter Window", image.BlueColorFilter());
    //image.DisplayOtherImage("GreenColorFilter Window", image.GreenColorFilter());
    //image.DisplayOtherImage("RedColorFilter Window", image.RedColorFilter());
    //image.DisplayOtherImage("ColorFilters Window", image.ColorFilters());

    image.DisplayOtherImage("Hough Window", image.HoughCircleMethod());
}
