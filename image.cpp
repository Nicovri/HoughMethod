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
        namedWindow(windowName); // Nomme la fenêtre d'affichage
        imshow(windowName, m_image); // Affiche cette fenêtre avec la matrice image membre de l'objet Image
        waitKey(0); // Attendre que l'utilisateur appuie sur une touche pour continuer le programme
    }
}

// Permet d'afficher une image retournée par une fonction sans que l'image d'origine ne soit modifiée
void Image::DisplayOtherImage(String windowName, Mat image)
{
    Mat imageSave = m_image.clone(); // Sauvegarde l'image d'origine
    m_image = image.clone(); // Récupère l'image extérieure à afficher dans la donnée membre
    if(m_image.empty()) {
        cout <<  "Could not open or find the image" << endl ;
    } else {
        namedWindow(windowName);
        imshow(windowName, m_image); // Affiche cette autre image dans une fenêtre
        waitKey(0);
    }
    m_image = imageSave.clone(); // Restitue à la donnée membre l'image d'origine
}

void Image::TransformGrayScale()
{
    cvtColor(m_image, m_image, cv::COLOR_BGR2GRAY); // Applique la fonction de changement de couleur d'une image
    //Paramètres : image source, image destination, couleur prédéfinie à appliquer (ici depuis BGR vers gris)
}

void Image::FiltrageMasque3x3(double a_11, double a_12, double a_13, double a_21, double a_22, double a_23,
                              double a_31, double a_32, double a_33)
{
    double masque[3][3] = {{a_11, a_12, a_13}, {a_21, a_22, a_23}, {a_31, a_32, a_33}}; // Masque en fonction des paramètres
    Mat kernel = Mat(3, 3, CV_64F, masque); // Création de la matrice qui correspond au masque souhaité
    filter2D(m_image, m_image, -1, kernel); // Applique un filtre 2D sur l'image
}

Mat Image::Histogramme()
{
    // Tableau d'entier pour chaque valeur d'intensité initialisé à 0
    int hist[256];
    for(int i = 0; i < 255; i++)
    {
        hist[i] = 0;
    }

    for(int i = 0; i < m_image.rows; i++) {
        for(int j = 0; j < m_image.cols; j++)
        {
            hist[(int)m_image.at<uchar>(i,j)]++;
        }
    }

    for(int i = 0; i < 256; i++)
        cout<<hist[i]<<" ";

    int hist_width = 512; int hist_height = 400;
    int line_width = cvRound((double) hist_width/256);

    Mat histImage(hist_height, hist_width, CV_8U, Scalar(255, 255, 255));

    int max = hist[0];
    for(int i = 1; i < 255; i++){
        if(max < hist[i]){
            max = hist[i];
        }
    }

    for(int i = 0; i < 255; i++){
        hist[i] = ((double)hist[i]/max)*histImage.rows;
    }

    for(int i = 0; i < 255; i++)
    {
        line(histImage, Point(line_width*(i), hist_height),Point(line_width*(i), hist_height - hist[i]),
             Scalar(0,0,0), 1, 8, 0);
    }
    return histImage;
}

Mat Image::ColorChannelInversionBlueRed()
{
    Mat imageInvert = m_image.clone();
    double zero;
    double deux;
    for(int x = 0; x < m_image.rows; x++) {
        for(int y = 0;y < m_image.cols; y++) {
            zero = imageInvert.at<Vec3b>(x, y)[0]; // Récupère la composante de la bande 0 (bleue) dans une variable
            deux = imageInvert.at<Vec3b>(x, y)[2]; // De même pour la composante de la bande 2 (rouge)
            imageInvert.at<Vec3b>(x, y)[0] = deux; // La composante bleue prend la valeur de la composante rouge
            imageInvert.at<Vec3b>(x, y)[2] = zero; // Et inversement
        }
    }
    return imageInvert;
}

Mat Image::BlueColorFilter()
{
    // Filtre bleu
    Mat imageB = m_image.clone(); // Copier la matrice de l'image d'origine dans une autre matrice
    for(int i = 0; i < imageB.rows; i++) {
        for(int j = 0;j < imageB.cols; j++) {
            imageB.at<Vec3b>(i,j)[1] = 0; // Idex correspondant à la bande de l'image (0 : bleu, 1 : vert, 2 : rouge)
            imageB.at<Vec3b>(i,j)[2] = 0; // Index 1 et 2 nuls pour tous les pixels de l'image = composante bleue uniquement
        }
    }
    return imageB;
}

Mat Image::GreenColorFilter()
{
    // Filtre vert
    Mat imageG = m_image.clone();
    for(int i = 0; i < imageG.rows; i++) {
        for(int j = 0;j < imageG.cols; j++) {
            imageG.at<Vec3b>(i,j)[0] = 0; // Index 0 et 2 nuls pour tous les pixels de l'image = composante verte uniquement
            imageG.at<Vec3b>(i,j)[2] = 0;
        }
    }
    return imageG;
}

Mat Image::RedColorFilter()
{
    // Filtre rouge
    Mat imageR = m_image.clone();
    for(int i = 0; i < imageR.rows; i++) {
        for(int j = 0;j < imageR.cols; j++) {
            imageR.at<Vec3b>(i,j)[0] = 0; // Index 0 et 1 nuls pour tous les pixels de l'image = composante rouge uniquement
            imageR.at<Vec3b>(i,j)[1] = 0;
        }
    }
    return imageR;
}

Mat Image::ColorFilters()
{
    // Filtre bleu
    Mat imageB = BlueColorFilter();

    // Filtre vert
    Mat imageG = GreenColorFilter();

    // Filtre rouge
    Mat imageR = RedColorFilter();

    Mat finalImage;
    hconcat(imageB, imageG, finalImage); // Concaténer le filtre bleu et le filtre vert horizontalement
    hconcat(finalImage, imageR, finalImage); //Concaténer les 3 filtres horizontalement
    return finalImage;
}

Mat Image::HoughCircleMethod()
{
    Mat imageGray;
    Mat imageColor = m_image.clone(); // Récupère la matrice image membre de l'objet Image
    cvtColor(m_image, imageGray, COLOR_BGR2GRAY); // Stocke l'image en nuances de gris dans imageGray (nécessaire pour utiliser la méthode HoughCircles)

    // Permet de cibler les formes qui sont vraiment des cercles (sinon l'algorithme en voit partout)
    // Plus le chiffre (impair) est grand, plus les cercles ciblés en sont vraiment
    // A partir de 5, seules les pièces sont ciblées
    medianBlur(imageGray, imageGray, 5);

    vector<Vec3f> cercles;
    HoughCircles(imageGray, cercles, CV_HOUGH_GRADIENT, 1, imageGray.rows/16, 100, 30, 20, 100);

    for(int i = 0;i < (int)cercles.size(); i++) {
        // Récupère chaque cercle ciblé par la méthode HoughCircles
        Vec3f cercle = cercles[i];

        // Point du centre de chaque cercle trouvé (index 0 et 1 du cercle, à savoir x et y)
        Point center = Point(cercle[0], cercle[1]);

        // Dessin d'un cercle sur imageColor, de centre center, de rayon 1, de couleur Scalar(B, G, R) et d'épaisseur de trait 2
        circle(imageColor, center, 1, Scalar(0, 150, 0), 2);

        // Récupère le rayon de chaque cercle trouvé (index 2 du cercle) et dessine un cercle sur imageColor
        int radius = cercle[2];
        circle(imageColor, center, radius, Scalar(200, 0, 0), 2);
    }
    return imageColor;
}

Mat Image::HoughLineMethod()
{

}
