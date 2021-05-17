#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>

using namespace cv;
using namespace std;

int main()
{
    String imgloc = "C:/Users/NicoVri/Pictures/Hough Images/Image1.png";
    Mat image;
    image= imread(imgloc);
    if(image.empty())
    {
       cout <<  "Could not open or find the image" << endl ;
       return -1;
    }
    namedWindow( "Display window" );
    imshow( "Display window", image );
    waitKey(0);
    return 0;

}
