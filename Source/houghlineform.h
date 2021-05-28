#ifndef HOUGHLINEFORM_H
#define HOUGHLINEFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "image.h"

/*
 * En-tête de la classe HoughLineForm, fenêtre de détection de lignes
 */
namespace Ui {
class HoughLineForm;
}

class HoughLineForm : public QWidget
{
    Q_OBJECT

public:
    explicit HoughLineForm(QWidget *parent = 0);
    ~HoughLineForm();

    // Données membres
    QString fileNameL;
    QImage imageL;
    Image imgL;
    String pathL;

    Image imgCannyL;
    Image imgHoughLine;

    QSize initialSizeL;
    QSize scaledSizeL;

    int n1L;
    int p1L;
    int n2L;
    int p2L;
    int n3L;
    int p3L;

private slots:

    // Gestionnaires d'événements
    void on_buttonOpenImageL_clicked();
    void on_buttonCannyL_clicked();
    void on_buttonHoughLine_clicked();
    void on_horizontalSliderParam1L_valueChanged();
    void on_horizontalSliderParam2L_valueChanged();
    void on_verticalSliderMinLineLength_valueChanged();
    void on_verticalSliderMaxLineGap_valueChanged();
    void on_buttonResetL_clicked();
    void on_buttonSaveCannyL_clicked();
    void on_buttonSaveHoughL_clicked();
    void on_pushButtonZoomOriginalL_clicked();
    void on_pushButtonZoomCannyL_clicked();
    void on_pushButtonZoomHoughL_clicked();

private:
    Ui::HoughLineForm *ui;

    // Fonctions membres
    void ApplyCanny();
    void ApplyHoughLineMethod();
    void ShowOrHideSliders(bool isVisible);
    void SetInitialSlidersValues();
    void ShowOrHideZoom(bool isVisible);
};

#endif // HOUGHLINEFORM_H
