#include "houghlineform.h"
#include "ui_houghlineform.h"

/*
 * Interface utilisateur pour la détection de lignes dans une image
 *
 * S'affiche en plein écran par défaut
 */
HoughLineForm::HoughLineForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HoughLineForm)
{
    ui->setupUi(this);

    ShowOrHideSliders(false);
    SetInitialSlidersValues();
    ShowOrHideZoom(false);
}

HoughLineForm::~HoughLineForm()
{
    delete ui;
}



//------------------
// Fonctions membres
//------------------

/*
 * Appliquer le filtre de Canny sur une image et l'afficher sur l'interface
 */
void HoughLineForm::ApplyCanny()
{
    // Récupère l'image initiale
    imgL.SetPath(pathL);
    imgL.SetImage(imread(pathL));

    // Applique le filtre de Canny de la classe Image pour les valeurs des sliders
    imgCannyL = imgL;
    imgCannyL.ApplyCanny(ui->horizontalSliderParam1L->value(), ui->horizontalSliderParam2L->value());

    // Convertit l'image en QImage nuances de gris (Indexed8)
    Mat matCannyL = imgCannyL.GetImage();
    QImage imageCannyL(matCannyL.data, matCannyL.cols, matCannyL.rows, matCannyL.step, QImage::Format_Indexed8);

    // Gestion de la taille de l'image (image ajustée avec la hauteur et la largeur de son son label par défaut)
    if(imageCannyL.height() > ui->labelCannyL->height() || imageCannyL.width() > ui->labelCannyL->width())
    {
        imageCannyL = imageCannyL.scaledToHeight(ui->labelCannyL->height(), Qt::SmoothTransformation);
        imageCannyL = imageCannyL.scaledToWidth(ui->labelCannyL->width(), Qt::SmoothTransformation);
    }

    // Affichage de l'image dans le label associé
    ui->labelCannyL->setPixmap(QPixmap::fromImage(imageCannyL));
}

/*
 * Appliquer la méthode de Hough pour les lignes sur un image et l'afficher sur l'interface
 */
void HoughLineForm::ApplyHoughLineMethod()
{
    // Récupère l'image initiale
    imgL.SetPath(pathL);
    imgL.SetImage(imread(pathL));

    // Applique la méthode de Hough pour les lignes de la classe Image pour les valeurs des sliders
    imgHoughLine = imgL;
    imgHoughLine.HoughLineMethod(ui->horizontalSliderParam1L->value(), ui->horizontalSliderParam2L->value(),
                                     ui->verticalSliderMinLineLength->value(), ui->verticalSliderMaxLineGap->value());

    // Convertit l'image BGR en image RGB
    imgHoughLine.ColorChannelInversionBlueRed();

    // Convertit l'image en QImage RGB (RGB888)
    Mat matHoughLine = imgHoughLine.GetImage();
    QImage imageHoughLine(matHoughLine.data, matHoughLine.cols, matHoughLine.rows, matHoughLine.step,
                            QImage::Format_RGB888);

    // Gestion de la taille de l'image (image ajustée par défaut)
    if(imageHoughLine.height() > ui->labelHoughLine->height() || imageHoughLine.width() > ui->labelHoughLine->width())
    {
        imageHoughLine = imageHoughLine.scaledToHeight(ui->labelHoughLine->height(), Qt::SmoothTransformation);
        imageHoughLine = imageHoughLine.scaledToWidth(ui->labelHoughLine->width(), Qt::SmoothTransformation);
    }

    // Affichage de l'image dans le label associé
    ui->labelHoughLine->setPixmap(QPixmap::fromImage(imageHoughLine));
}

/*
 * Rend les sliders utilisables
 *
 * isVisible : est-ce que les sliders peuvent être utilisés ?
 */
void HoughLineForm::ShowOrHideSliders(bool isVisible)
{
    ui->horizontalSliderParam1L->setEnabled(isVisible);
    ui->horizontalSliderParam2L->setEnabled(isVisible);
    ui->verticalSliderMaxLineGap->setEnabled(isVisible);
    ui->verticalSliderMinLineLength->setEnabled(isVisible);

    ui->labelL->setEnabled(isVisible);
    ui->label_2L->setEnabled(isVisible);
    ui->label_3L->setEnabled(isVisible);
    ui->label_4L->setEnabled(isVisible);
}

/*
 * Valeurs par défaut des sliders (paramètres variables des méthodes Canny et HoughCircles dans la classe Image
 */
void HoughLineForm::SetInitialSlidersValues()
{
    ui->horizontalSliderParam1L->setValue(250);
    ui->horizontalSliderParam2L->setValue(250);
    ui->verticalSliderMaxLineGap->setValue(250);
    ui->verticalSliderMinLineLength->setValue(0);
}

/*
 * Affichage des boutons de zoom pour la gestion de la taille des images
 *
 * isVisible : est-ce que les boutons doivent être affichés ?
 */
void HoughLineForm::ShowOrHideZoom(bool isVisible)
{
    ui->label_5L->setVisible(isVisible);
    ui->pushButtonZoomOriginalL->setVisible(isVisible);
    ui->pushButtonZoomCannyL->setVisible(isVisible);
    ui->pushButtonZoomHoughL->setVisible(isVisible);
    ui->line_3->setVisible(isVisible);
}



//---------------------------
// Gestionnaires d'événements
//---------------------------

/*
 * Clic sur le bouton pour ouvrir une image
 */
void HoughLineForm::on_buttonOpenImageL_clicked()
{
    // Permet d'éviter un bug d'affichage lors de l'ouverture d'une nouvelle image si le zoom est activé
    if(n1L == p1L) {
        imageL = imageL.scaled(scaledSizeL, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->labelOriginalImageL->setPixmap(QPixmap::fromImage(imageL));
    }

    // QFileDialog : boite de dialogue d'ouverture d'un fichier image
    fileNameL = QFileDialog::getOpenFileName(this, "Choose an image", "C://", "*.png *.jpg *.jpeg");
    // Si le chemin d'accès n'est pas nul
    if(QString::compare(fileNameL, QString()) != 0) {

        bool valid = imageL.load(fileNameL);
        // Et si l'image a été chargée
        if(valid) {

            // Gestion de la taille : affichage ajusté par défaut et on récupère les tailles des images pour sa gestion
            initialSizeL = QSize(imageL.width(), imageL.height());
            if(imageL.height() > ui->labelOriginalImageL->height() || imageL.width() > ui->labelOriginalImageL->width())
            {
                imageL = imageL.scaledToHeight(ui->labelOriginalImageL->height(), Qt::SmoothTransformation);
                imageL = imageL.scaledToWidth(ui->labelOriginalImageL->width(), Qt::SmoothTransformation);
                scaledSizeL = QSize(imageL.width(), imageL.height());
            }

            // Affichage de l'image dans le label associé
            ui->labelOriginalImageL->setPixmap(QPixmap::fromImage(imageL));

            // Valeurs par défaut modifiées / D'autres boutons sont accessibles / Les labels sont vidés
            ui->buttonCannyL->setEnabled(true);
            ui->buttonOpenImageL->setEnabled(false);
            SetInitialSlidersValues();
            ShowOrHideSliders(false);
            ShowOrHideZoom(false);
            ui->buttonResetL->setEnabled(false);
            ui->buttonSaveCannyL->setEnabled(false);
            ui->buttonSaveHoughL->setEnabled(false);
            ui->labelCannyL->clear();
            ui->labelHoughLine->clear();
            // Paramètres de la gestion du zoom initialisés
            n1L = 0;
            p1L = 1;
            n2L = 0;
            p2L = 1;
            n3L = 0;
            p3L = 1;

            // Récupère le chemin d'accès au format String
            pathL = fileNameL.toLocal8Bit().constData();
        }
    }
}

/*
 * Clic sur le bouton pour le filtre de Canny
 */
void HoughLineForm::on_buttonCannyL_clicked()
{
    // Applique et affiche l'image du filtrage de Canny
    ApplyCanny();

    // Nouveau bouton accessible
    ui->buttonHoughLine->setEnabled(true);
    ui->buttonCannyL->setEnabled(false);
    ui->buttonSaveCannyL->setEnabled(true);
}

/*
 * Clic sur le bouton de la détection de cercles
 */
void HoughLineForm::on_buttonHoughLine_clicked()
{
    // Applique et affiche l'image de détection des lignes
    ApplyHoughLineMethod();

    // Nouveaux boutons et sliders accessibles
    ui->buttonOpenImageL->setEnabled(true);
    ui->buttonHoughLine->setEnabled(false);
    ui->buttonSaveHoughL->setEnabled(true);
    ShowOrHideSliders(true);
    ui->buttonResetL->setEnabled(true);

    // Test pour l'affichage ou non des boutons de zoom (seulement si l'image est trop grande)
    imgL.SetPath(pathL);
    imgL.SetImage(imread(pathL));
    Mat mat = imgL.GetImage();
    QImage imageTestL(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    if(imageTestL.height() > ui->labelOriginalImageL->height() || imageTestL.width() > ui->labelOriginalImageL->width())
    {
        ShowOrHideZoom(true);
    }
}

/*
 * Modification de la valeur du slider controllant param1
 */
void HoughLineForm::on_horizontalSliderParam1L_valueChanged()
{
    // Effectuer à nouveau la  détection et afficher le nouveau résultat en temps réel
    ApplyCanny();
    ApplyHoughLineMethod();
}

/*
 * Modification de la valeur du slider controllant param2
 */
void HoughLineForm::on_horizontalSliderParam2L_valueChanged()
{
    // De même
    ApplyCanny();
    ApplyHoughLineMethod();
}

/*
 * Modification de la valeur du slider controllant minLineLength
 */
void HoughLineForm::on_verticalSliderMinLineLength_valueChanged()
{
    // Effectuer à nouveau la méthode de Hough pour afficher le résultat en temps réel
    ApplyHoughLineMethod();
}

/*
 * Modification de la valeur du slider controllant maxLineGap
 */
void HoughLineForm::on_verticalSliderMaxLineGap_valueChanged()
{
    ApplyHoughLineMethod();
}

/*
 * Clic sur le bouton de réinitialisation
 */
void HoughLineForm::on_buttonResetL_clicked()
{
    // Valeurs des sliders par défaut
    SetInitialSlidersValues();

    // Appliquer et afficher les nouveaux résultats pour les images
    ApplyCanny();
    ApplyHoughLineMethod();

    // MessageBox qui informe l'utilisateur du résultat
    QMessageBox::information(this, "Reset", "The default values have been applied.");
}

/*
 * Clic sur le bouton de sauvegarde de l'image du filtrage de Canny
 */
void HoughLineForm::on_buttonSaveCannyL_clicked()
{
    // Si l'image n'est pas vide
    if(!imgCannyL.GetImage().empty()) {
        // Récupère le chemin d'accès où l'utilisateur veut enregistrer l'image
        QString dirNameL = QFileDialog::getSaveFileName(this, "Save file", "C://", "JPEG (*.jpg *.jpeg);;PNG (*.png)");

        // S'il n'est pas vide, on continue
        if(!dirNameL.isEmpty()) {
            // Conversion en String du chemin d'accès
            String pathSaveL = dirNameL.toLocal8Bit().constData();

            // Ecriture de l'image au chemin choisi
            imwrite(pathSaveL, imgCannyL.GetImage());

            // MessageBox du bon fonctionnement de l'enregistrement
            QMessageBox::information(this, "Saved", "The Canny image has been saved successfully !");
        } else {

            // MessageBox si l'enregistrement à été annulé
            QMessageBox::critical(this, "Canceled", "Your demand has been canceled...");
        }
    }
}

/*
 * Clic sur le bouton de sauvegarde de l'image de Hough (même fonctionnement)
 */
void HoughLineForm::on_buttonSaveHoughL_clicked()
{
    if(!imgHoughLine.GetImage().empty()) {
        QString dirNameL = QFileDialog::getSaveFileName(this, "Save file", "C://", "JPEG (*.jpg *.jpeg);;PNG (*.png)");

        if(!dirNameL.isEmpty()) {
            String pathSaveL = dirNameL.toLocal8Bit().constData();

            // Inversion des couleurs pour récupérer une image BGR
            imgHoughLine.ColorChannelInversionBlueRed();

            imwrite(pathSaveL, imgHoughLine.GetImage());
            QMessageBox::information(this, "Saved", "The HoughCircle image has been saved successfully !");
        } else {
            QMessageBox::critical(this, "Canceled", "Your demand has been canceled...");
        }
    }
}

/*
 * Clic sur le bouton de zoom sur l'image initiale
 */
void HoughLineForm::on_pushButtonZoomOriginalL_clicked()
{
    // Récupère l'image initiale
    imgL.SetPath(pathL);
    imgL.SetImage(imread(pathL));

    // Si l'image n'est pas vide, on la traite avant de la convertir et de l'afficher dans le label à la bonne taille
    //(bonnes couleurs , non inversées peu importe le nombre de fois où on appuie sur le bouton)
    if(!imgL.GetImage().empty()) {
        Image imageSizeL = imgL;
        imageSizeL.ColorChannelInversionBlueRed();
        Mat matSizeL = imageSizeL.GetImage();
        QImage qimageSizeL(matSizeL.data, matSizeL.cols, matSizeL.rows, matSizeL.step, QImage::Format_RGB888);

        // Boucle alternant entre l'un et l'autre des cas : au départ n1L=0 != p1L=1, puis n1L=p1L, n1L!=p1L, n1L=p1L, etc.
        if(n1L != p1L) {
            n1L++;

            // Image de grande taille (zoomée, pas affichée en entier donc des scrollbars apparaissent)
            qimageSizeL = qimageSizeL.scaled(initialSizeL, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelOriginalImageL->setPixmap(QPixmap::fromImage(qimageSizeL));
        } else {
            p1L++;

            // Image de taille ajustée (dézoomée, visible en entier)
            qimageSizeL = qimageSizeL.scaled(scaledSizeL, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelOriginalImageL->setPixmap(QPixmap::fromImage(qimageSizeL));
        }
    }
}

/*
 * Clic sur le bouton de zoom sur l'image du filtrage de Canny
 */
void HoughLineForm::on_pushButtonZoomCannyL_clicked()
{
    // Conversion de l'image en QImage après s'être assuré qu'elle n'est pas vide
    if(!imgCannyL.GetImage().empty()) {
        Image imageSizeCannyL = imgCannyL;
        Mat matSizeCannyL = imageSizeCannyL.GetImage();
        QImage qimageSizeCannyL(matSizeCannyL.data, matSizeCannyL.cols, matSizeCannyL.rows, matSizeCannyL.step,
                               QImage::Format_Indexed8);

        // Boucle qui alterne entre image zoomée et image dézoomée (voir méthode clic sur le bouton de zoom image initiale)
        if(n2L != p2L) {
            n2L++;

            qimageSizeCannyL = qimageSizeCannyL.scaled(initialSizeL, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelCannyL->setPixmap(QPixmap::fromImage(qimageSizeCannyL));
        } else {
            p2L++;

            qimageSizeCannyL = qimageSizeCannyL.scaled(scaledSizeL, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelCannyL->setPixmap(QPixmap::fromImage(qimageSizeCannyL));
        }
    }
}

/*
 * Clic sur le bouton de zoom sur l'image de Hough pour les cercles
 */
void HoughLineForm::on_pushButtonZoomHoughL_clicked()
{
    // Conversion de l'image en QImage après s'être assuré qu'elle n'est pas vide
    if(!imgHoughLine.GetImage().empty()) {
        Image imageSizeHoughL = imgHoughLine;
        Mat matSizeHoughL = imageSizeHoughL.GetImage();
        QImage qimageSizeHoughL(matSizeHoughL.data, matSizeHoughL.cols, matSizeHoughL.rows, matSizeHoughL.step,
                               QImage::Format_RGB888);

        // Boucle qui alterne entre image zoomée et image dézoomée (voir méthode clic sur le bouton de zoom image initiale)
        if(n3L != p3L) {
            n3L++;

            qimageSizeHoughL = qimageSizeHoughL.scaled(initialSizeL, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelHoughLine->setPixmap(QPixmap::fromImage(qimageSizeHoughL));
        } else {
            p3L++;

            qimageSizeHoughL = qimageSizeHoughL.scaled(scaledSizeL, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelHoughLine->setPixmap(QPixmap::fromImage(qimageSizeHoughL));
        }
    }
}
