#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "grafico.h"
#include <QMainWindow>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>       // Incluye texto no editable por el usuario
#include <QLineEdit>    // Incluye barras de textos
#include <QPushButton>  // Incluye los botones
#include <QString>      // Incluye una libreria de string
#include <QCheckBox>    // Incluye botones con check
#include <QCompleter>   // Incluye un listado para autocompletar
#include <QStringList>          // Crea una lista de un conjunto de palabras
#include <QRegularExpression>   // Verifica el formato de entradas de usuario, extraer información de texto o validar datos.
#include <QVBoxLayout>          // Pone los widget en una fila para abajo.
#include <QStringListModel>
#include <QListWidget>
#include <QCloseEvent>  // Para manejar el evento de cierre
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString Confirmarm();                   // Valida el minimo
    QString ConfirmarM();                   // Valida el maximo
    void GuardarMm();                       // Guardar el maximo y el minimo

private slots:
    void Ejecutar();                        // Slot para ejecutar toda las funciones

private:
    Ui::MainWindow *ui;

    // Relacionado con ingreso de ecuacion
    QLabel *tituloE;               // Titulo de la ecuacion
    QLineEdit *BarraE;             // Barra de texto para ingresar la ecuación
    QString GuardarE;              // Variable para almacenar la ecuación

    // Relacionado con los ingreso del minimo
    QLabel *tituloMin;               // Titulo del minimo
    QLineEdit *BarraMin;             // Barra de texto para minimo
    float Guardarm;               // Variable para almacenar el minimo

    // Relacionado con los ingreso del maximo
    QLabel *tituloMax;               // Titulo del maximo
    QLineEdit *BarraMax;             // Barra de texto para maximo
    float GuardarM;               // Variable para almacenar el maximo

    // Gráfico
    GraficoWidget *graf;
    QPushButton *BotonActualizar; // Botón para actualizar el gráfico

    // Botones para finalizar
    QPushButton *BotonEj;          // Botón para ejecutar
    QPushButton *BotonAlto;        // Botón reiniciar
};

#endif // MAINWINDOW_H
