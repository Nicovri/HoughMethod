#include"image.hpp"

Image::Image()
{
    m_path = "";
    m_image = imread(m_path);
}

Image::Image(String path)
{
    m_path = path;
    m_image = imread(m_path);
}

Image::~Image() { }

void Image::DisplayImage(String windowName)
{
    if(m_image.empty()) {
        cout <<  "Could not open or find the image" << endl ;
    } else {
        namedWindow(windowName);
        imshow(windowName, m_image);
        waitKey(0);
    }
}

void Image::TransformGrayScale()
{
    cvtColor(m_image, m_image, cv::COLOR_BGR2GRAY);
}

void Image::FiltrageMasque3x3(double a_11, double a_12, double a_13, double a_21, double a_22, double a_23,
                              double a_31, double a_32, double a_33)
{
    double masque[3][3] = {{a_11, a_12, a_13}, {a_21, a_22, a_23}, {a_31, a_32, a_33}};
    Mat kernel = Mat(3, 3, CV_64F, masque);
    filter2D(m_image, m_image, -1, kernel);
}

/*Mat Image::Histogramme()
{
    int hist[256];

    for(int i = 0; i < 255; i++)
    {
        hist[i] = 0;
    }

    for(int y = 0; y < m_image.rows; y++)
        for(int x = 0; x < m_image.cols; x++)
            hist[(int)m_image.at<uchar>(y,x)]++;

    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double) hist_w/256);

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    int max = hist[0];
    for(int i = 1; i < 256; i++){
        if(max < hist[i]){
            max = hist[i];
        }
    }

    for(int i = 0; i < 255; i++){
        hist[i] = ((double)hist[i]/max)*histImage.rows;
    }

    for(int i = 0; i < 255; i++)
    {
        line(histImage, Point(bin_w*(i), hist_h),Point(bin_w*(i), hist_h - hist[i]),
             Scalar(0,0,0), 1, 8, 0);
    }
    return histImage;
}*/

void Image::ColorChannelInversionBlueRed()
{
    double zero;
    double deux;
    for(int x = 0; x < m_image.rows; x++) {
        for(int y = 0;y < m_image.cols; y++) {
            zero = m_image.at<Vec3b>(x, y)[0];
            deux = m_image.at<Vec3b>(x, y)[2];
            m_image.at<Vec3b>(x, y)[0] = deux;
            m_image.at<Vec3b>(x, y)[2] = zero;
        }
    }
}

void Image::DisplayBlueColorFilter()
{
    // Filtre bleu
    Mat imageB = m_image.clone();
    Mat image1 = m_image.clone();
    for(int i = 0; i < imageB.rows; i++) {
        for(int j = 0;j < imageB.cols; j++) {
            imageB.at<Vec3b>(i,j)[1] = 0;
            imageB.at<Vec3b>(i,j)[2] = 0;
        }
    }
    m_image = imageB.clone();
    DisplayImage("Image Window");
    m_image = image1.clone();
}

void Image::DisplayGreenColorFilter()
{
    // Filtre vert
    Mat imageG = m_image.clone();
    Mat image1 = m_image.clone();
    for(int i = 0; i < imageG.rows; i++) {
        for(int j = 0;j < imageG.cols; j++) {
            imageG.at<Vec3b>(i,j)[0] = 0;
            imageG.at<Vec3b>(i,j)[2] = 0;
        }
    }
    m_image = imageG.clone();
    DisplayImage("Image Window");
    m_image = image1.clone();
}

void Image::DisplayRedColorFilter()
{
    // Filtre rouge
    Mat imageR = m_image.clone();
    Mat image1 = m_image.clone();
    for(int i = 0; i < imageR.rows; i++) {
        for(int j = 0;j < imageR.cols; j++) {
            imageR.at<Vec3b>(i,j)[0] = 0;
            imageR.at<Vec3b>(i,j)[1] = 0;
        }
    }
    m_image = imageR.clone();
    DisplayImage("Image Window");
    m_image = image1.clone();
}

void Image::DisplayColorFilters()
{
    // Filtre bleu
    Mat imageB = m_image.clone();
    for(int i = 0; i < imageB.rows; i++) {
        for(int j = 0;j < imageB.cols; j++) {
            imageB.at<Vec3b>(i,j)[1] = 0;
            imageB.at<Vec3b>(i,j)[2] = 0;
        }
    }

    // Filtre vert
    Mat imageG = m_image.clone();
    for(int i = 0; i < imageG.rows; i++) {
        for(int j = 0;j < imageG.cols; j++) {
            imageG.at<Vec3b>(i,j)[0] = 0;
            imageG.at<Vec3b>(i,j)[2] = 0;
        }
    }

    // Filtre rouge
    Mat imageR = m_image.clone();
    for(int i = 0; i < imageR.rows; i++) {
        for(int j = 0;j < imageR.cols; j++) {
            imageR.at<Vec3b>(i,j)[0] = 0;
            imageR.at<Vec3b>(i,j)[1] = 0;
        }
    }

    Mat image1 = m_image.clone();
    Mat finalImage;
    hconcat(imageB, imageG, finalImage);
    hconcat(finalImage, imageR, finalImage);
    m_image = finalImage.clone();
    DisplayImage("Color Filters Window");
    m_image = image1.clone();
}
