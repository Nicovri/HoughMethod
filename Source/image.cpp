#include"image.h"

/*
 *  Constructeur par défaut
 */
Image::Image()
{
    m_path = "";
    m_image = imread(m_path);
}

/*
 *  Constructeur avec le chemin d'accès passé en paramètre
 */
Image::Image(String path)
{
    m_path = path;
    m_image = imread(m_path);
}

/*
 * Destructeur
 */
Image::~Image() { }

// Accesseurs  et mutateurs des données membres de la classe Image
String Image::GetPath() { return m_path; }

void Image::SetPath(String Path) { m_path = Path; }

Mat Image::GetImage() { return m_image; }

void Image::SetImage(Mat Img) {m_image = Img.clone(); }

/*
 *  Inversion des bandes bleues et rouges d'une image
 *
 * OpenCV : image BGR
 * Qt : image RGB
 */
void Image::ColorChannelInversionBlueRed()
{
    double zero;
    double deux;
    for(int x = 0; x < m_image.rows; x++) {
        for(int y = 0;y < m_image.cols; y++) {
            // Récupère la composante de la bande 0 (bleue) dans une variable
            zero = m_image.at<Vec3b>(x, y)[0];
            // De même pour la composante de la bande 2 (rouge)
            deux = m_image.at<Vec3b>(x, y)[2];

            // La composante bleue prend la valeur de la composante rouge
            m_image.at<Vec3b>(x, y)[0] = deux;
            // Et inversement
            m_image.at<Vec3b>(x, y)[2] = zero;
        }
    }
}

/*
 *  Filtrage de Canny (image noire, bords des objets en blanc)
 *
 * param1 : seuil 1 du filtre
 * param2 : seuil 2 du filtre
 */
void Image::ApplyCanny(int param1, int param2)
{
    Canny(m_image, m_image, param1, param2);
}

/*
 *  Algorithme de Hough pour la détection de cercles
 *
 * param1 : seuil 1 de la méthode Canny
 * param2 : seuil 2 de la méthode Canny
 * minRadius : rayon minimum des cercles détectés
 * maxRadius : rayon maximum des cercles détectés
 */
void Image::HoughCircleMethod(int param1, int param2, int minRadius, int maxRadius)
{
    // Image en nuances de gris
    Mat imageGray;
    cvtColor(m_image, imageGray, COLOR_BGR2GRAY);

    // Permet de cibler les formes qui sont vraiment des cercles (sinon l'algorithme en voit partout)
    // A partir de 5, seules les pièces (de l'image Pieces.png) sont ciblées
    medianBlur(imageGray, imageGray, 5);

    // Filtre de Canny
    Canny(imageGray, imageGray, param1, param2);

    // Liste de vecteurs à 3 coordonnées qui représente des cercles (abscisse [0], ordonnée [1], rayon [2])
    vector<Vec3f> cercles;

    /*
     *  Utilisation de la méthode HoughCircles
     *
     * Paramètres :
     *
     * Image source
     * Liste de stockage des cercles
     * Méthode utilisée (gradient de Hough)
     * Résolution de l'accumulateur
     * Distance minimale entre les cercles détectés
     * Seuil de l'image
     * Seuil de l'accumulateur
     * minRadius
     * maxRadius
     */
    HoughCircles(imageGray, cercles, CV_HOUGH_GRADIENT, 1, imageGray.rows/16, 100, 30, minRadius, maxRadius);

    for(int i = 0;i < (int)cercles.size(); i++) {
        Vec3f cercle = cercles[i];

        // Centre de chaque cercle trouvé
        Point center = Point(cercle[0], cercle[1]);
        // Dessin d'un cercle sur m_image, de centre center, de rayon 1 pixel, de couleur Scalar(B, G, R) et d'épaisseur de trait 2
        circle(m_image, center, 1, Scalar(0, 150, 0), 2);

        // Dessin du cercle de rayon radius
        int radius = cercle[2];
        circle(m_image, center, radius, Scalar(0, 0, 200), 2);
    }
}

/*
 *  Algorithme de Hough pour la détection de lignes
 *
 * param1 : seuil 1 de Canny
 * param2 : seuil 2 de Canny
 * minLineLength : longueur minimum des lignes détectées
 * maxLineGap : distance maximum entre deux points d'une ligne
 */
void Image::HoughLineMethod(int param1, int param2, double minLineLength, double maxLineGap)
{
    Mat imageEdges;
    // Filtrage Canny
    Canny(m_image, imageEdges, param1, param2);

    // Liste de vecteurs à 4 coordonnées (abscisse point 1 [0], ordonnée point 1 [1], abscisse point 2 [2], ordonnée point 2 [3]=
    vector<Vec4i> lines;

    /*
     * Utilisation de la méthode HoughLinesP
     *
     * Paramètres :
     *
     * Image source
     * Liste de stockage des lignes
     * Résolution en distance de l'accumulateur
     * Résolution en angle de l'accumulateur
     * Seuil de l'accumulateur
     * minLineLength
     * maxLineGap
     */
    HoughLinesP(imageEdges, lines, 1, CV_PI/180, 50, minLineLength, maxLineGap);

    for(int i = 0;i < (int)lines.size();i++) {
        Vec4i l = lines[i];

        // Dessin des lignes avec deux points donnés par le vecteur à 4 coordonnées, de couleur Scalar(B, G, R) et d'épaisseur 3
        line(m_image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3);
    }
}










/*
 *  Méthode utilisée pour un projet console qui affiche l'image dans une fenêtre dont on choisi le nom
 */
void Image::DisplayImage(String windowName)
{
    if(m_image.empty()) {
        cout <<  "Could not open or find the image" << endl ;
    } else {
        // Nomme la fenêtre d'affichage
        namedWindow(windowName);

        // Affiche cette fenêtre avec la matrice image
        imshow(windowName, m_image);

        // Attendre que l'utilisateur appuie sur une touche pour continuer le programme
        waitKey(0);
    }
}

/*
 *  Transforme l'image couleur en image en nuances de gris
 */
void Image::TransformGrayScale()
{
    cvtColor(m_image, m_image, cv::COLOR_BGR2GRAY);
}

/*
 * Application d'un filtre 3x3 sur l'image dont les éléments sont choisi par l'utilisateur
 */
void Image::FiltrageMasque3x3(double a_11, double a_12, double a_13, double a_21, double a_22, double a_23,
                              double a_31, double a_32, double a_33)
{
    // Tableau de valeurs qui correspond au masque en fonction des paramètres
    double masque[3][3] = {{a_11, a_12, a_13}, {a_21, a_22, a_23}, {a_31, a_32, a_33}};

    // Création de la matrice qui correspond au masque souhaité
    Mat kernel = Mat(3, 3, CV_64F, masque);

    // Applique un filtre 2D sur l'image
    filter2D(m_image, m_image, -1, kernel);
}

/*
 *  Fonction qui retourne l'histogramme d'une image en nuances de gris
 */
Mat Image::Histogramme()
{
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

/*
 *  Filtre bleu
 */
Mat Image::BlueColorFilter()
{
    Mat imageB = m_image.clone();
    for(int i = 0; i < imageB.rows; i++) {
        for(int j = 0;j < imageB.cols; j++) {
            // Idex correspondant à la bande de l'image (0 : bleu, 1 : vert, 2 : rouge)
            // Index 1 et 2 nuls pour tous les pixels de l'image = composante bleue uniquement
            imageB.at<Vec3b>(i,j)[1] = 0;
            imageB.at<Vec3b>(i,j)[2] = 0;
        }
    }
    return imageB;
}

/*
 *  Filtre vert
 */
Mat Image::GreenColorFilter()
{
    Mat imageG = m_image.clone();
    for(int i = 0; i < imageG.rows; i++) {
        for(int j = 0;j < imageG.cols; j++) {
            // Index 0 et 2 nuls pour tous les pixels de l'image = composante verte uniquement
            imageG.at<Vec3b>(i,j)[0] = 0;
            imageG.at<Vec3b>(i,j)[2] = 0;
        }
    }
    return imageG;
}

/*
 *  Filtre rouge
 */
Mat Image::RedColorFilter()
{
    Mat imageR = m_image.clone();
    for(int i = 0; i < imageR.rows; i++) {
        for(int j = 0;j < imageR.cols; j++) {
            // Index 0 et 1 nuls pour tous les pixels de l'image = composante rouge uniquement
            imageR.at<Vec3b>(i,j)[0] = 0;
            imageR.at<Vec3b>(i,j)[1] = 0;
        }
    }
    return imageR;
}

/*
 *  Retourne les 3 filtres de couleur de l'image
 */
Mat Image::ColorFilters()
{
    // Filtre bleu
    Mat imageB = BlueColorFilter();

    // Filtre vert
    Mat imageG = GreenColorFilter();

    // Filtre rouge
    Mat imageR = RedColorFilter();

    Mat finalImage;
    // Concaténer le filtre bleu et le filtre vert horizontalement
    hconcat(imageB, imageG, finalImage);
    // Puis concaténer les 3 filtres horizontalement
    hconcat(finalImage, imageR, finalImage);
    return finalImage;
}
