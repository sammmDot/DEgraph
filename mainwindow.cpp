#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicializar el gráfico
    graf = new GraficoWidget(this);
    graf->setGeometry(20, 20, 1000, 720);

    tituloE = new QLabel("Ingrese la ecuacion:", this);
    tituloE->setGeometry(1080, 180, 200, 20); // Posición (x, y) y tamaño ancho x alto
    tituloE->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    // Intput ecuaciones
    BarraE = new QLineEdit(this);             // Crea la barra de texto
    BarraE->setGeometry(1080, 200, 200, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra
    //Caracterristicas de la barra
    BarraE->setStyleSheet("QLineEdit {"
                          "border-radius: 10px;"
                          "padding: 5px;"
                          "background-color: #b4ddd8;"
                          "}");

    tituloMin = new QLabel("Tiempo inicial:", this);
    tituloMin->setGeometry(1080, 280, 100, 20); // Posición (x, y) y tamaño ancho x alto
    tituloMin->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;");

    // Intput minimo
    BarraMin = new QLineEdit(this);             // Crea la barra de texto
    //Caracterristicas de la barra
    BarraMin->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #b4ddd8;"
                            "}");
    BarraMin->setGeometry(1080, 300, 100, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    tituloMax = new QLabel("Tiempo final:", this);
    tituloMax->setGeometry(1220, 280, 100, 20); // Posición (x, y) y tamaño ancho x alto
    tituloMax->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    // Imput maximo
    BarraMax = new QLineEdit(this);              // Crea la barra de texto
    //Caracterristicas de la barra
    BarraMax->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #b4ddd8;"
                            "}");
    BarraMax->setGeometry(1220, 300, 100, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra


    // Boton ejecutar
    BotonEj = new QPushButton("Ejecutar", this);
        // Caracteristicas del boton
    BotonEj->setStyleSheet("QPushButton{""border-radius: 10px;""background-color: #bef2af;""font-weight: bold;""}"
                           "QPushButton:hover {""background-color: #8aeb81;""}"
                           "QPushButton:pressed {""background-color: #8aeb81;""}"
                           );
    BotonEj->setGeometry(1080, 600, 100, 50);  // Ubicacion
    connect(BotonEj, &QPushButton::clicked, this, &MainWindow::Ejecutar);  // Conectar el clic del botón al slot Ejecutar

}


MainWindow::~MainWindow() {
    delete ui;
}

// Funciones para validar las variables del minimo y el maximo
QString MainWindow::Confirmarm(){
    QString m = BarraMin->text();

    bool conversionOk;
    double minValue = m.toFloat(&conversionOk);  // Intenta convertir m a número

    if (!conversionOk) {  // Si falla la conversión
        if (m.isEmpty()) {
            QMessageBox::warning(this, "Error", "No ingresó el mínimo.");
        } else {
            QMessageBox::warning(this, "Error", "El valor mínimo no es válido. Por favor, usa solo números.");
        }
        BarraMin->setStyleSheet("QLineEdit {"
                                "border-radius: 10px;"
                                "padding: 5px;"
                                "background-color: #f5c2bd;"
                                "}");
        return "";  // Retorna cadena vacía para indicar error
    }
    BarraMin->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #b4ddd8;"
                            "}");
    return m;  // Devuelve el valor si es válido
}

QString MainWindow::ConfirmarM(){
    QString M = BarraMax->text();

    bool conversionOk;
    double maxValue = M.toDouble(&conversionOk);  // Intenta convertir M a número
    if (!conversionOk) {  // Si falla la conversión
        if (M.isEmpty()) {
            QMessageBox::warning(this, "Error", "No ingresó el máximo.");
        } else {
            QMessageBox::warning(this, "Error", "El valor máximo no es válido. Por favor, usa solo números.");
        }
        BarraMax->setStyleSheet("QLineEdit {"
                                "border-radius: 10px;"
                                "padding: 5px;"
                                "background-color: #f5c2bd;"
                                "}");
        return "";  // Retorna cadena vacía para indicar error
    }
    BarraMax->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #b4ddd8;"
                            "}");
    return M;  // Devuelve el valor si es válido
}
void MainWindow::GuardarMm(){
    QString m = Confirmarm();
    QString M = ConfirmarM();

    if (m.isEmpty() || M.isEmpty()) {
        return;  // Termina la función si hubo error previo en m o M
    }

    // Conversión
    bool conversionOk1, conversionOk2;
    float min = m.toFloat(&conversionOk1);
    float max = M.toFloat(&conversionOk2);

    if (conversionOk1 && conversionOk2) {
        if (min < max && 0 <=min) {
            Guardarm = min;   // Guardar mínimo
            GuardarM = max;   // Guardar máximo

            if (conversionOk1 && conversionOk2) {
                // Pasar los valores a GraficoWidget2000
                graf->setT(min);  // Actualizar t
                graf->setT1(max); // Actualizar t1
                QMessageBox::information(this, "Éxito", "Gráfico actualizado.");
            } else {
                QMessageBox::warning(this, "Error", "Los valores de t o t1 no son válidos.");
            }
            BarraMin->setStyleSheet("QLineEdit {"
                                    "border-radius: 10px;"
                                    "padding: 5px;"
                                    "background-color: #b4ddd8;"
                                    "}");
            BarraMax->setStyleSheet("QLineEdit {"
                                    "border-radius: 10px;"
                                    "padding: 5px;"
                                    "background-color: #b4ddd8;"
                                    "}");
        } else {
            if (min > max ){
                QMessageBox::warning(this, "Error", "El tiempo inicial no puede ser mayor o igual que el final.");
                BarraMin->setStyleSheet("QLineEdit {"
                                        "border-radius: 10px;"
                                        "padding: 5px;"
                                        "background-color: #f5c2bd;"
                                        "}");
                BarraMax->setStyleSheet("QLineEdit {"
                                        "border-radius: 10px;"
                                        "padding: 5px;"
                                        "background-color: #f5c2bd;"
                                        "}");
            }else{
                QMessageBox::warning(this, "Error", "el tiempo no puede ser negativo");
                BarraMin->setStyleSheet("QLineEdit {"
                                        "border-radius: 10px;"
                                        "padding: 5px;"
                                        "background-color: #f5c2bd;"
                                        "}");
            }

        }
    }
}

void MainWindow::Ejecutar() {
    GuardarMm();
}
