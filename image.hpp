#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>

using namespace cv;
using namespace std;

class Image
{
    String m_path;
    Mat m_image;

public:
    Image();
    Image(String path);
    ~Image();

    void DisplayImage(String windowName);
    void TransformGrayScale();
    void FiltrageMasque3x3(double a_11, double a12, double a_13, double a_21, double a_22, double a_23,
                           double a_31, double a_32, double a_33);
    //Mat Histogramme();
    void ColorChannelInversionBlueRed();

    void DisplayBlueColorFilter();
    void DisplayGreenColorFilter();
    void DisplayRedColorFilter();
    void DisplayColorFilters();
};
