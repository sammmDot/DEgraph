#include "mainwindow.h"

#include <QApplication>

//para ejecutar el programa desd la terminal:  make && ./interfaz0


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("DeGraph"); // Título de la ventana
    w.setStyleSheet("background-color: #e4e4e4;"); // Cambiar el color
    w.resize(2000,900);
    w.show();
    return a.exec();
}
