#pragma once

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
 * Classe gérant l'accès et la modification d'un image OpenCV
 *
 * m_path : chemin d'accès de l'image
 * m_image : image sous forme de matrice pour OpenCV
 *
 *
 */
class Image
{
    // Données membres
    String m_path;
    Mat m_image;

public:
    // Constructeurs, destructeur
    Image();
    Image(String path);
    ~Image();

    // Accesseurs, mutateurs
    String GetPath();
    void SetPath(String Path);
    Mat GetImage();
    void SetImage(Mat Img);

    // Méthodes utiles à l'utilisation de la tranformée de Hough
    void ColorChannelInversionBlueRed();
    void ApplyCanny(int param1, int param2);
    void HoughCircleMethod(int param1, int param2, int minRadius, int maxRadius);
    void HoughLineMethod(int param1, int param2, double minLineLength, double maxLineGap);





    // Méthodes de prise en main d'OpenCV
    void DisplayImage(String windowName);
    void TransformGrayScale();
    void FiltrageMasque3x3(double a_11, double a12, double a_13,
                           double a_21, double a_22, double a_23,
                           double a_31, double a_32, double a_33);
    Mat Histogramme();
    Mat BlueColorFilter();
    Mat GreenColorFilter();
    Mat RedColorFilter();
    Mat ColorFilters();
    //
};
