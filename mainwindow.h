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
    //ventana principal
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void GuardaEcu();                       // Valida y guardan las ecuación
    QString Confirmarm();                   // Valida el minimo
    QString ConfirmarM();                   // Valida el maximo
    void GuardarMm();                       // Guardar el maximo y el minimo
    void GuardarSub();                      // Valida y guardan las subdivisiones
    void Autocompletar();                   // Inicialisa el autocompletado

private slots:
    // Slots para botones de ayuda al usuario
    void BAE();
    void BAMm();
    void BAS();
    void BAZ();

    //Funciones
    void Ejecutar();                        // Slot para ejecutar toda las funciones
    void ReiniciarTodo();                  // Slot para reiniciar variables
    void Check(int state);                 // Slot para manejar cambios de estado de la caja

    void Glosario();                       // Slot para crear una ventana nueva

private:
    Ui::MainWindow *ui;

    QLabel *Titulo;

    // Botones de ayuda
    QPushButton *BotonAE;        // Boton ayuda ecuacion
    QPushButton *BotonAMm;       // Boton ayuda minimo y maximo
    QPushButton *BotonAS;        // Boton ayuda Subdivicion
    QPushButton *BotonAZ;        // Boton ayuda eje z

    // Relacionado con ingreso de ecuacion
    QLabel *tituloE;               // Titulo de la ecuacion
    QLineEdit *BarraE;             // Barra de texto para ingresar la ecuación
    float GuardarE;              // Variable para almacenar la ecuación
    QStringListModel *model;       // Agrega una lista
    QCompleter *completar;         // Completa las funciones matematicas

    // Relacionado con los ingreso del minimo
    QLabel *tituloMin;               // Titulo del minimo
    QLineEdit *BarraMin;             // Barra de texto para minimo
    float Guardarm;               // Variable para almacenar el minimo

    // Relacionado con los ingreso del maximo
    QLabel *tituloMax;               // Titulo del maximo
    QLineEdit *BarraMax;             // Barra de texto para maximo
    float GuardarM;               // Variable para almacenar el maximo

    // Relacionado con los ingreso de subdivisiones
    QLabel *tituloS;                 // Titulo del maximo
    QLineEdit *BarraS;              // Barra de texto para ingreso de subdivisiones
    float GuardarS;               // Variable para almacenar cuanto se va a dividr el eje

    // Relacionado con el boton de check
    QLabel *tituloC;                 // Subtitulo del boton
    QCheckBox *BotonC;               // Boton check

    // Botones para finalizar
    QPushButton *BotonEj;          // Botón para ejecutar
    QPushButton *BotonAlto;        // Botón reiniciar

    // Boton de glosario
    QPushButton *BotonGlo;          // Boton para abrir un nueva ventana

    //Grafico
    Grafico *graf;
};



class SecondWindow : public QWidget {
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void mostrarDescripcion(QListWidgetItem *item);

private:
    QLabel *titulo;                 //texto de la ventana
    QLabel *Glo;                    //texto de la ventana
    QLabel *descriptionLabel;       //texto de la ventana
    QVBoxLayout *G;
    QListWidget *listG;             // Lista de funciones
};

#endif // MAINWINDOW_H
