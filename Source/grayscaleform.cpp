#include "grayscaleform.h"
#include "ui_grayscaleform.h"

GrayscaleForm::GrayscaleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrayscaleForm)
{
    ui->setupUi(this);
}

GrayscaleForm::~GrayscaleForm()
{
    delete ui;
}

void GrayscaleForm::on_buttonOpenAndGray_clicked()
{
    fileNameG = QFileDialog::getOpenFileName(this, "Choose an image", "C://", "*.png *.jpg *.jpeg *.bmp *.gif");
    if(QString::compare(fileNameG, QString()) != 0) {
        bool valid = imageG.load(fileNameG);
        if(valid) {

            initialSizeG = QSize(imageG.width(), imageG.height());
            if(imageG.height() > ui->labelOriginalImage->height() || imageG.width() > ui->labelOriginalImage->width())
            {
                imageG = imageG.scaledToHeight(ui->labelOriginalImage->height(), Qt::SmoothTransformation);
                imageG = imageG.scaledToWidth(ui->labelOriginalImage->width(), Qt::SmoothTransformation);
            }

            ui->labelOriginalImage->setPixmap(QPixmap::fromImage(imageG));

            pathG = fileNameG.toLocal8Bit().constData();
            imgG.SetPath(pathG);
            imgG.SetImage(imread(pathG));

            ui->buttonSave->setEnabled(true);

            imgGray = imgG;
            imgGray.TransformGrayScale();
            Mat matGray = imgGray.GetImage();
            QImage imageGray(matGray.data, matGray.cols, matGray.rows, matGray.step, QImage::Format_Indexed8);

            if(imageGray.height() > ui->labelGrayImage->height() || imageGray.width() > ui->labelGrayImage->width())
            {
                imageGray = imageGray.scaledToHeight(ui->labelGrayImage->height(), Qt::SmoothTransformation);
                imageGray = imageGray.scaledToWidth(ui->labelGrayImage->width(), Qt::SmoothTransformation);
            }
            ui->labelGrayImage->setPixmap(QPixmap::fromImage(imageGray));
        }
    }
}

void GrayscaleForm::on_buttonSave_clicked()
{
    if(!imgGray.GetImage().empty()) {
        QString dirNameG = QFileDialog::getSaveFileName(this, "Save file", "C://", "JPEG (*.jpg *.jpeg);;PNG (*.png)");

        if(!dirNameG.isEmpty()) {
            String pathSave = dirNameG.toLocal8Bit().constData();
            imwrite(pathSave, imgGray.GetImage());
            QMessageBox::information(this, "Saved", "The gray image has been saved successfully !");
        } else {
            QMessageBox::critical(this, "Canceled", "Your demand has been canceled...");
        }
    }
}
