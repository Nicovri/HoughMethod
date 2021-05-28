#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMdiSubWindow>

#include "grayscaleform.h"
#include "filter3form.h"
#include "houghcircleform.h"
#include "houghlineform.h"

/*
 * Fenêtre principale de l'interface graphique
 *
 * MDI parent
 * S'affiche en plein écran par défaut
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Fonction membre pour charger une fenêtre
 */
void MainWindow::loadSubWindow(QWidget *widget)
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->setWindowTitle(widget->windowTitle());
    window->setWindowIcon(widget->windowIcon());
    window->adjustSize();
    window->showMaximized();
}

/*
 * Afficher le formulaire HoughCircleForm en appuyant sur le bouton de menu correspondant
 */
void MainWindow::on_actionCircle_triggered()
{
    loadSubWindow(new HoughCircleForm(this));
}

/*
 * De même pour HoughLineForm
 */
void MainWindow::on_actionLines_triggered()
{
    loadSubWindow(new HoughLineForm(this));
}



// Forms de prise en main de Qt
void MainWindow::on_actionGrayscale_triggered()
{
    loadSubWindow(new GrayscaleForm(this));
}

void MainWindow::on_action3x3_Filter_triggered()
{
    loadSubWindow(new Filter3Form(this));
}
