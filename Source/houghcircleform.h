#ifndef HOUGHCIRCLEFORM_H
#define HOUGHCIRCLEFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "image.h"

/*
 * En-tête de la classe HoughCircleForm, fenêtre de détection de cercles
 */
namespace Ui {
class HoughCircleForm;
}

class HoughCircleForm : public QWidget
{
    Q_OBJECT

public:
    explicit HoughCircleForm(QWidget *parent = 0);
    ~HoughCircleForm();

    // Données membres
    QString fileName;
    QImage image;
    Image img;
    String path;

    Image imgCanny;
    Image imgHoughCircle;

    QSize initialSize;
    QSize scaledSize;

    int n1;
    int p1;
    int n2;
    int p2;
    int n3;
    int p3;

private slots:

    // Gestionnaires d'événements
    void on_buttonOpenImage_clicked();
    void on_buttonCanny_clicked();
    void on_buttonHoughCircle_clicked();
    void on_horizontalSliderParam1_valueChanged();
    void on_horizontalSliderParam2_valueChanged();
    void on_verticalSliderMinRadius_valueChanged(int value);
    void on_verticalSliderMaxRadius_valueChanged(int value);
    void on_buttonReset_clicked();
    void on_buttonSaveCanny_clicked();
    void on_buttonSaveHough_clicked();
    void on_pushButtonZoomOriginal_clicked();
    void on_pushButtonZoomCanny_clicked();
    void on_pushButtonZoomHough_clicked();

private:
    Ui::HoughCircleForm *ui;

    // Fonctions membres
    void ApplyCanny();
    void ApplyHoughCircleMethod();
    void ShowOrHideSliders(bool isVisible);
    void SetInitialSlidersValues();
    void ShowOrHideZoom(bool isVisible);
};

#endif // HOUGHCIRCLEFORM_H
