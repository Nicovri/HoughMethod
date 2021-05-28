#include "filter3form.h"
#include "ui_filter3form.h"

Filter3Form::Filter3Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filter3Form)
{
    ui->setupUi(this);
}

Filter3Form::~Filter3Form()
{
    delete ui;
}

void Filter3Form::ClearLineEdit()
{
    ui->lineEditA11->clear();
    ui->lineEditA12->clear();
    ui->lineEditA13->clear();
    ui->lineEditA21->clear();
    ui->lineEditA22->clear();
    ui->lineEditA23->clear();
    ui->lineEditA31->clear();
    ui->lineEditA32->clear();
    ui->lineEditA33->clear();
}

void Filter3Form::on_buttonOpen_clicked()
{
    fileNameF = QFileDialog::getOpenFileName(this, "Choose an image", "C://", "*.png *.jpg *.jpeg *.bmp *.gif");
    if(QString::compare(fileNameF, QString()) != 0) {
        bool valid = imageF.load(fileNameF);
        if(valid) {

            initialSizeF = QSize(imageF.width(), imageF.height());
            if(imageF.height() > ui->labelOriginalImage->height() || imageF.width() > ui->labelOriginalImage->width())
            {
                imageF = imageF.scaledToHeight(ui->labelOriginalImage->height(), Qt::SmoothTransformation);
                imageF = imageF.scaledToWidth(ui->labelOriginalImage->width(), Qt::SmoothTransformation);
            }

            ui->labelOriginalImage->setPixmap(QPixmap::fromImage(imageF));

            pathF = fileNameF.toLocal8Bit().constData();
            imgF.SetPath(pathF);
            imgF.SetImage(imread(pathF));

            ui->buttonBox->setEnabled(true);

            ui->buttonFilter1->setEnabled(true);
            ui->buttonFilter2->setEnabled(true);
            ui->buttonFilter3->setEnabled(true);
            ui->buttonFilter4->setEnabled(true);
            ui->buttonFilter5->setEnabled(true);

            ui->lineEditA11->setEnabled(true);
            ui->lineEditA12->setEnabled(true);
            ui->lineEditA13->setEnabled(true);
            ui->lineEditA21->setEnabled(true);
            ui->lineEditA22->setEnabled(true);
            ui->lineEditA23->setEnabled(true);
            ui->lineEditA31->setEnabled(true);
            ui->lineEditA32->setEnabled(true);
            ui->lineEditA33->setEnabled(true);

            ClearLineEdit();
        }
    }
}

void Filter3Form::on_buttonBox_accepted()
{

}

void Filter3Form::on_buttonBox_rejected()
{

}

void Filter3Form::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text() == "Reset") {
        ClearLineEdit();
    } else {

    }
}
