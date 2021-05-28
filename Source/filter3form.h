#ifndef FILTER3FORM_H
#define FILTER3FORM_H

#include <QWidget>
#include <QAbstractButton>
#include <QFileDialog>

#include "image.h"

namespace Ui {
class Filter3Form;
}

class Filter3Form : public QWidget
{
    Q_OBJECT

public:
    explicit Filter3Form(QWidget *parent = 0);
    ~Filter3Form();

    QString fileNameF;
    QImage imageF;
    Image imgF;
    String pathF;

    Image imgFilter;

    QSize initialSizeF;

private slots:
    void on_buttonOpen_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Filter3Form *ui;

    void ClearLineEdit();
};

#endif // FILTER3FORM_H
