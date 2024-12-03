#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("DeGraph"); // Título de la ventana
    w.resize(2000, 1000); // Ancho y largo de la ventana
    w.setStyleSheet("background-color: #e4e4e4;"); // Cambiar el color
    w.show();
    return a.exec();
}

