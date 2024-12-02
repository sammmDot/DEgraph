#include "mainwindow.h"

#include <QApplication>

//para ejecutar el programa desd la terminal:  make && ./interfaz0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("DeGraph"); // Título de la ventana
    w.resize(1000, 1000); // Ancho y largo de la ventana
    w.setStyleSheet("background-color: #e4e4e4;"); // Cambiar el color
    w.show();
    return a.exec();
}

