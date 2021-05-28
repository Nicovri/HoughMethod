#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*
 * En-tête de la classe MainWindow, fenêtre principale de l'interface
 */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    // Gestionnaires d'événements
    void on_actionCircle_triggered();
    void on_actionLines_triggered();

    void on_actionGrayscale_triggered();
    void on_action3x3_Filter_triggered();

private:
    Ui::MainWindow *ui;

    // Fonction membre de chargement des fenêtres
    void loadSubWindow(QWidget *widget);
};

#endif // MAINWINDOW_H
