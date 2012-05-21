#include <QtGui/QApplication>
#include <QSplashScreen>
#include <QProgressBar>
#include "mainwindow.h"
//#include "ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/tv.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    //a.processEvents();

    MainWindow w;

    splash->showMessage("Hello I am a Spash",Qt::AlignBottom,Qt::black);
    w.show();
    splash->finish(&w);
    return a.exec();
}
