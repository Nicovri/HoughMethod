#ifndef GRAYSCALEFORM_H
#define GRAYSCALEFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "image.h"

namespace Ui {
class GrayscaleForm;
}

class GrayscaleForm : public QWidget
{
    Q_OBJECT

public:
    explicit GrayscaleForm(QWidget *parent = 0);
    ~GrayscaleForm();

    QString fileNameG;
    QImage imageG;
    Image imgG;
    String pathG;

    Image imgGray;

    QSize initialSizeG;

private slots:
    void on_buttonOpenAndGray_clicked();

    void on_buttonSave_clicked();

private:
    Ui::GrayscaleForm *ui;
};

#endif // GRAYSCALEFORM_H
