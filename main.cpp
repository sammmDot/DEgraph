#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("DeGraph"); // Título de la ventana
    w.resize(1000, 2000); // Ancho y largo de la ventana
    w.show();
    return a.exec();
}
