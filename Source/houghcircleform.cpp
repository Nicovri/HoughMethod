#include "houghcircleform.h"
#include "ui_houghcircleform.h"

/*
 * Interface utilisateur pour la détection de cercles dans une image
 *
 * S'affiche en plein écran par défaut
 */
HoughCircleForm::HoughCircleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HoughCircleForm)
{
    ui->setupUi(this);

    ShowOrHideSliders(false);
    SetInitialSlidersValues();
    ShowOrHideZoom(false);
}

HoughCircleForm::~HoughCircleForm()
{
    delete ui;
}



//------------------
// Fonctions membres
//------------------

/*
 * Appliquer le filtre de Canny sur une image et l'afficher sur l'interface
 */
void HoughCircleForm::ApplyCanny()
{
    // Récupère l'image initiale
    img.SetPath(path);
    img.SetImage(imread(path));

    // Applique le filtre de Canny de la classe Image pour les valeurs des sliders
    imgCanny = img;
    imgCanny.ApplyCanny(ui->horizontalSliderParam1->value(), ui->horizontalSliderParam2->value());

    // Convertit l'image en QImage nuances de gris (Indexed8)
    Mat matCanny = imgCanny.GetImage();
    QImage imageCanny(matCanny.data, matCanny.cols, matCanny.rows, matCanny.step, QImage::Format_Indexed8);

    // Gestion de la taille de l'image (image ajustée avec la hauteur et la largeur de son son label par défaut)
    if(imageCanny.height() > ui->labelCanny->height() || imageCanny.width() > ui->labelCanny->width())
    {
        imageCanny = imageCanny.scaledToHeight(ui->labelCanny->height(), Qt::SmoothTransformation);
        imageCanny = imageCanny.scaledToWidth(ui->labelCanny->width(), Qt::SmoothTransformation);
    }

    // Affichage de l'image dans le label associé
    ui->labelCanny->setPixmap(QPixmap::fromImage(imageCanny));
}

/*
 * Appliquer la méthode de Hough pour les cercles sur un image et l'afficher sur l'interface
 */
void HoughCircleForm::ApplyHoughCircleMethod()
{
    // Récupère l'image initiale
    img.SetPath(path);
    img.SetImage(imread(path));

    // Applique la méthode de Hough pour les cercles de la classe Image pour les valeurs des sliders
    imgHoughCircle = img;
    imgHoughCircle.HoughCircleMethod(ui->horizontalSliderParam1->value(), ui->horizontalSliderParam2->value(),
                                     ui->verticalSliderMinRadius->value(), ui->verticalSliderMaxRadius->value());

    // Convertit l'image BGR en image RGB
    imgHoughCircle.ColorChannelInversionBlueRed();

    // Convertit l'image en QImage RGB (RGB888)
    Mat matHoughCircle = imgHoughCircle.GetImage();
    QImage imageHoughCircle(matHoughCircle.data, matHoughCircle.cols, matHoughCircle.rows, matHoughCircle.step,
                            QImage::Format_RGB888);

    // Gestion de la taille de l'image (image ajustée par défaut)
    if(imageHoughCircle.height() > ui->labelHoughCircle->height() || imageHoughCircle.width() > ui->labelHoughCircle->width())
    {
        imageHoughCircle = imageHoughCircle.scaledToHeight(ui->labelHoughCircle->height(), Qt::SmoothTransformation);
        imageHoughCircle = imageHoughCircle.scaledToWidth(ui->labelHoughCircle->width(), Qt::SmoothTransformation);
    }

    // Affichage de l'image dans le label associé
    ui->labelHoughCircle->setPixmap(QPixmap::fromImage(imageHoughCircle));
}

/*
 * Rend les sliders utilisables
 *
 * isVisible : est-ce que les sliders peuvent être utilisés ?
 */
void HoughCircleForm::ShowOrHideSliders(bool isVisible)
{
    ui->horizontalSliderParam1->setEnabled(isVisible);
    ui->horizontalSliderParam2->setEnabled(isVisible);
    ui->verticalSliderMaxRadius->setEnabled(isVisible);
    ui->verticalSliderMinRadius->setEnabled(isVisible);

    ui->label->setEnabled(isVisible);
    ui->label_2->setEnabled(isVisible);
    ui->label_3->setEnabled(isVisible);
    ui->label_4->setEnabled(isVisible);
}

/*
 * Valeurs par défaut des sliders (paramètres variables des méthodes Canny et HoughCircles dans la classe Image
 */
void HoughCircleForm::SetInitialSlidersValues()
{
    ui->horizontalSliderParam1->setValue(250);
    ui->horizontalSliderParam2->setValue(250);
    ui->verticalSliderMaxRadius->setValue(250);
    ui->verticalSliderMinRadius->setValue(0);
}

/*
 * Affichage des boutons de zoom pour la gestion de la taille des images
 *
 * isVisible : est-ce que les boutons doivent être affichés ?
 */
void HoughCircleForm::ShowOrHideZoom(bool isVisible)
{
    ui->label_6->setVisible(isVisible);
    ui->pushButtonZoomOriginal->setVisible(isVisible);
    ui->pushButtonZoomCanny->setVisible(isVisible);
    ui->pushButtonZoomHough->setVisible(isVisible);
    ui->line_3->setVisible(isVisible);
}



//---------------------------
// Gestionnaires d'événements
//---------------------------

/*
 * Clic sur le bouton pour ouvrir une image
 */
void HoughCircleForm::on_buttonOpenImage_clicked()
{
    // Permet d'éviter un bug d'affichage lors de l'ouverture d'une nouvelle image si le zoom est activé
    if(n1 == p1) {
        image = image.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->labelOriginalImage->setPixmap(QPixmap::fromImage(image));
    }

    // QFileDialog : boite de dialogue d'ouverture d'un fichier image
    fileName = QFileDialog::getOpenFileName(this, "Choose an image", "C://", "*.png *.jpg *.jpeg");
    // Si le chemin d'accès n'est pas nul
    if(QString::compare(fileName, QString()) != 0) {

        bool valid = image.load(fileName);
        // Et si l'image a été chargée
        if(valid) {

            // Gestion de la taille : affichage ajusté par défaut et on récupère les tailles des images pour sa gestion
            initialSize = QSize(image.width(), image.height());
            if(image.height() > ui->labelOriginalImage->height() || image.width() > ui->labelOriginalImage->width())
            {
                image = image.scaledToHeight(ui->labelOriginalImage->height(), Qt::SmoothTransformation);
                image = image.scaledToWidth(ui->labelOriginalImage->width(), Qt::SmoothTransformation);
                scaledSize = QSize(image.width(), image.height());
            }

            // Affichage de l'image dans le label associé
            ui->labelOriginalImage->setPixmap(QPixmap::fromImage(image));

            // Valeurs par défaut modifiées / D'autres boutons sont accessibles / Les labels sont vidés
            ui->buttonCanny->setEnabled(true);
            ui->buttonOpenImage->setEnabled(false);
            SetInitialSlidersValues();
            ShowOrHideSliders(false);
            ShowOrHideZoom(false);
            ui->buttonReset->setEnabled(false);
            ui->buttonSaveCanny->setEnabled(false);
            ui->buttonSaveHough->setEnabled(false);
            ui->labelCanny->clear();
            ui->labelHoughCircle->clear();
            // Paramètres de la gestion du zoom initialisés
            n1 = 0;
            p1 = 1;
            n2 = 0;
            p2 = 1;
            n3 = 0;
            p3 = 1;

            // Récupère le chemin d'accès au format String
            path = fileName.toLocal8Bit().constData();
        }
    }
}

/*
 * Clic sur le bouton pour le filtre de Canny
 */
void HoughCircleForm::on_buttonCanny_clicked()
{
    // Applique et affiche l'image du filtrage de Canny
    ApplyCanny();

    // Nouveau bouton accessible
    ui->buttonHoughCircle->setEnabled(true);
    ui->buttonCanny->setEnabled(false);
    ui->buttonSaveCanny->setEnabled(true);

}

/*
 * Clic sur le bouton de la détection de cercles
 */
void HoughCircleForm::on_buttonHoughCircle_clicked()
{
    // Applique et affiche l'image de détection des cercles
    ApplyHoughCircleMethod();

    // Nouveaux boutons et sliders accessibles
    ui->buttonOpenImage->setEnabled(true);
    ui->buttonHoughCircle->setEnabled(false);
    ui->buttonSaveHough->setEnabled(true);
    ShowOrHideSliders(true);
    ui->buttonReset->setEnabled(true);

    // Test pour l'affichage ou non des boutons de zoom (seulement si l'image est trop grande)
    img.SetPath(path);
    img.SetImage(imread(path));
    Mat mat = img.GetImage();
    QImage imageTest(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    if(imageTest.height() > ui->labelOriginalImage->height() || imageTest.width() > ui->labelOriginalImage->width())
    {
        ShowOrHideZoom(true);
    }
}

/*
 * Modification de la valeur du slider controllant param1
 */
void HoughCircleForm::on_horizontalSliderParam1_valueChanged()
{
    // Effectuer à nouveau la  détection et afficher le nouveau résultat en temps réel
    ApplyCanny();
    ApplyHoughCircleMethod();
}

/*
 * Modification de la valeur du slider controllant param2
 */
void HoughCircleForm::on_horizontalSliderParam2_valueChanged()
{
    // De même
    ApplyCanny();
    ApplyHoughCircleMethod();
}

/*
 * Modification de la valeur du slider controllant minRadius
 *
 * value : valeur de ce slider au moment de l'exécution de ce code
 */
void HoughCircleForm::on_verticalSliderMinRadius_valueChanged(int value)
{
    // Bloque le slider s'il va plus loin que celui de maxRadius (si sa valeur devient plus grande, plus aucun cercles détectés)
    if(value > ui->verticalSliderMaxRadius->value()) {
        value = ui->verticalSliderMaxRadius->value();
        ui->verticalSliderMinRadius->setValue(value);
    }

    // Effectuer à nouveau la méthode de Hough pour afficher le résultat en temps réel
    ApplyHoughCircleMethod();
}

/*
 * Modification de la valeur du slider controllant maxRadius
 *
 * value : valeur de ce slider au moment de l'exécution de ce code
 */
void HoughCircleForm::on_verticalSliderMaxRadius_valueChanged(int value)
{
    // Bloque le slider s'il va plus loin que minRadius (pour les mêmes raisons)
    if(value < ui->verticalSliderMinRadius->value()) {
        value = ui->verticalSliderMinRadius->value();
        ui->verticalSliderMaxRadius->setValue(value);
    }

    ApplyHoughCircleMethod();
}

/*
 * Clic sur le bouton de réinitialisation
 */
void HoughCircleForm::on_buttonReset_clicked()
{
    // Valeurs des sliders par défaut
    SetInitialSlidersValues();

    // Appliquer et afficher les nouveaux résultats pour les images
    ApplyCanny();
    ApplyHoughCircleMethod();

    // MessageBox qui informe l'utilisateur du résultat
    QMessageBox::information(this, "Reset", "The default values have been applied.");
}

/*
 * Clic sur le bouton de sauvegarde de l'image du filtrage de Canny
 */
void HoughCircleForm::on_buttonSaveCanny_clicked()
{
    // Si l'image n'est pas vide
    if(!imgCanny.GetImage().empty()) {
        // Récupère le chemin d'accès où l'utilisateur veut enregistrer l'image
        QString dirName = QFileDialog::getSaveFileName(this, "Save file", "C://", "JPEG (*.jpg *.jpeg);;PNG (*.png)");

        // S'il n'est pas vide, on continue
        if(!dirName.isEmpty()) {
            // Conversion en String du chemin d'accès
            String pathSave = dirName.toLocal8Bit().constData();

            // Ecriture de l'image au chemin choisi
            imwrite(pathSave, imgCanny.GetImage());

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
void HoughCircleForm::on_buttonSaveHough_clicked()
{
    if(!imgHoughCircle.GetImage().empty()) {
        QString dirName = QFileDialog::getSaveFileName(this, "Save file", "C://", "JPEG (*.jpg *.jpeg);;PNG (*.png)");

        if(!dirName.isEmpty()) {
            String pathSave = dirName.toLocal8Bit().constData();

            // Inversion des couleurs pour récupérer une image BGR
            imgHoughCircle.ColorChannelInversionBlueRed();

            imwrite(pathSave, imgHoughCircle.GetImage());
            QMessageBox::information(this, "Saved", "The HoughCircle image has been saved successfully !");
        } else {
            QMessageBox::critical(this, "Canceled", "Your demand has been canceled...");
        }
    }
}

/*
 * Clic sur le bouton de zoom sur l'image initiale
 */
void HoughCircleForm::on_pushButtonZoomOriginal_clicked()
{
    // Récupère l'image initiale
    img.SetPath(path);
    img.SetImage(imread(path));

    // Si l'image n'est pas vide, on la traite avant de la convertir et de l'afficher dans le label à la bonne taille
    //(bonnes couleurs , non inversées peu importe le nombre de fois où on appuie sur le bouton)
    if(!img.GetImage().empty()) {
        Image imageSize = img;
        imageSize.ColorChannelInversionBlueRed();
        Mat matSize = imageSize.GetImage();
        QImage qimageSize(matSize.data, matSize.cols, matSize.rows, matSize.step, QImage::Format_RGB888);

        // Boucle alternant entre l'un et l'autre des cas : au départ n1=0 != p1=1, puis n1=p1, n1!=p1, n1=p1, etc.
        if(n1 != p1) {
            n1++;

            // Image de grande taille (zoomée, pas affichée en entier donc des scrollbars apparaissent)
            qimageSize = qimageSize.scaled(initialSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelOriginalImage->setPixmap(QPixmap::fromImage(qimageSize));
        } else {
            p1++;

            // Image de taille ajustée (dézoomée, visible en entier)
            qimageSize = qimageSize.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelOriginalImage->setPixmap(QPixmap::fromImage(qimageSize));
        }
    }
}

/*
 * Clic sur le bouton de zoom sur l'image du filtrage de Canny
 */
void HoughCircleForm::on_pushButtonZoomCanny_clicked()
{
    // Conversion de l'image en QImage après s'être assuré qu'elle n'est pas vide
    if(!imgCanny.GetImage().empty()) {
        Image imageSizeCanny = imgCanny;
        Mat matSizeCanny = imageSizeCanny.GetImage();
        QImage qimageSizeCanny(matSizeCanny.data, matSizeCanny.cols, matSizeCanny.rows, matSizeCanny.step,
                               QImage::Format_Indexed8);

        // Boucle qui alterne entre image zoomée et image dézoomée (voir méthode clic sur le bouton de zoom image initiale)
        if(n2 != p2) {
            n2++;

            qimageSizeCanny = qimageSizeCanny.scaled(initialSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelCanny->setPixmap(QPixmap::fromImage(qimageSizeCanny));
        } else {
            p2++;

            qimageSizeCanny = qimageSizeCanny.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelCanny->setPixmap(QPixmap::fromImage(qimageSizeCanny));
        }
    }
}

/*
 * Clic sur le bouton de zoom sur l'image de Hough pour les cercles
 */
void HoughCircleForm::on_pushButtonZoomHough_clicked()
{
    // Conversion de l'image en QImage après s'être assuré qu'elle n'est pas vide
    if(!imgHoughCircle.GetImage().empty()) {
        Image imageSizeHough = imgHoughCircle;
        Mat matSizeHough = imageSizeHough.GetImage();
        QImage qimageSizeHough(matSizeHough.data, matSizeHough.cols, matSizeHough.rows, matSizeHough.step,
                               QImage::Format_RGB888);

        // Boucle qui alterne entre image zoomée et image dézoomée (voir méthode clic sur le bouton de zoom image initiale)
        if(n3 != p3) {
            n3++;

            qimageSizeHough = qimageSizeHough.scaled(initialSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelHoughCircle->setPixmap(QPixmap::fromImage(qimageSizeHough));
        } else {
            p3++;

            qimageSizeHough = qimageSizeHough.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->labelHoughCircle->setPixmap(QPixmap::fromImage(qimageSizeHough));
        }
    }
}
