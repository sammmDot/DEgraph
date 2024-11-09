#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QLabel>       // Incluye texto no editable por el usuario
#include <QLineEdit>    // Incluye barras de textos
#include <QPushButton>  // Incluye los botones
#include <QString>      // Incluye una libreria de string
#include <QCheckBox>    // Incluye botones con check

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
    void GuardaEcu();                       // Valida y guardan las ecuación
    QString Confirmarm();                   // Valida el minimo
    QString ConfirmarM();                   // Valida el maximo
    void GuardarMm();                       // Guardar el maximo y el minimo
    void GuardarSub();                      // Valida y guardan las subdivisiones

private slots:
    void Ejecutar();                        // Slot para ejecutar toda las funciones
    void ReiniciarTodo();
    void Check(int state);                 // Slot para manejar cambios de estado de la caja

private:
    Ui::MainWindow *ui;
    // Extras
    QLabel *tituloG;               // Titulo

    // Relacionado con ingreso de ecuacion
    QLabel *tituloE;               // Titulo de la ecuacion
    QLineEdit *BarraE;             // Barra de texto para ingresar la ecuación
    QString GuardarE;              // Variable para almacenar la ecuación

    //Relacionado con los ingreso del minimo
    QLabel *tituloMin;               // Titulo del minimo
    QLineEdit *BarraMin;             // Barra de texto para minimo
    QString Guardarm;               // Variable para almacenar el minimo

    //Relacionado con los ingreso del maximo
    QLabel *tituloMax;               // Titulo del maximo
    QLineEdit *BarraMax;             // Barra de texto para maximo
    QString GuardarM;               // Variable para almacenar el maximo

    //Relacionado con los ingreso de subdivisiones
    QLabel *tituloS;                 // Titulo del maximo
    QLineEdit *BarraS;              // Barra de texto para ingreso de subdivisiones
    QString GuardarS;               // Variable para almacenar cuanto se va a dividr el eje

    //Relacionado con el boton de check
    QLabel *tituloC;                 // Subtitulo del boton
    QCheckBox *BotonC;               // Boton check

    // Botones para finalizar
    QPushButton *BotonEj;          // Botón para ejecutar
    QPushButton *BotonAlto;        // Botón reiniciar
};
#endif // MAINWINDOW_H
