#include "mainwindow.h"
#include <QApplication>

/*
 * main.cpp complété automatiquement par le logiciel. Affiche la fenêtre principale MainWindow
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
