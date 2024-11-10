#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>          // Aparece otra ventan con un mensaje
#include <QRegularExpression>   // Verifica el formato de entradas de usuario, extraer información de texto o validar datos

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    // Texto
    tituloG = new QLabel("DGraph", this);
    tituloG->setGeometry(700, 30, 250, 20);   // Posición (x, y) y tamaño ancho x alto
    tituloG->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");  // Caracteristicas generales
    tituloG->setAlignment(Qt::AlignCenter);   // Centtra el texto

    tituloE = new QLabel("Ingrese la ecuacion:", this);
    tituloE->setGeometry(700, 80, 200, 20); // Posición (x, y) y tamaño ancho x alto
    tituloE->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    tituloMin = new QLabel("Minimo:", this);
    tituloMin->setGeometry(700, 180, 100, 20); // Posición (x, y) y tamaño ancho x alto
    tituloMin->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;");

    tituloMax = new QLabel("Maximo:", this);
    tituloMax->setGeometry(850, 180, 100, 20); // Posición (x, y) y tamaño ancho x alto
    tituloMax->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    tituloS = new QLabel("Subdivision:", this);
    tituloS->setGeometry(700, 280, 250, 20); // Posición (x, y) y tamaño ancho x alto
    tituloS->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    tituloC = new QLabel("Eje z:", this);
    tituloC->setGeometry(730, 405, 250, 20); // Posición (x, y) y tamaño ancho x alto
    tituloC->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    // Intput ecuaciones
    BarraE = new QLineEdit(this);             // Crea la barra de texto
    BarraE->setGeometry(700, 100, 250, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Intput minimo
    BarraMin = new QLineEdit(this);             // Crea la barra de texto
    BarraMin->setGeometry(700, 200, 100, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Imput maximo
    BarraMax = new QLineEdit(this);              // Crea la barra de texto
    BarraMax->setGeometry(850, 200, 100, 30);    // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Imput subdivision
    BarraS = new QLineEdit(this);              // Crea la barra de texto
    BarraS->setGeometry(700, 300, 250, 30);    // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Boton check
    BotonC = new QCheckBox(this);
    BotonC->setGeometry(700, 400, 200, 30); // Posición y tamaño de check
    connect(BotonC, &QCheckBox::stateChanged, this, &MainWindow::Check);  //conecta el boton con una condicion

    // Boton ejecutar
    BotonEj = new QPushButton("Ejecutar", this);
        // Caracteristicas del boton
    BotonEj->setStyleSheet("QPushButton{""border-radius: 10px;""background-color: #bef2af;""font-weight: bold;""}"
                           "QPushButton:hover {""background-color: #8aeb81;""}"
                           "QPushButton:pressed {""background-color: #8aeb81;""}"
                           );
    BotonEj->setGeometry(700, 500, 120, 30);  // Ubicacion

    // Boton detener
    BotonAlto = new QPushButton("Detener", this);
        // Caracteristicas del boton
    BotonAlto->setStyleSheet("QPushButton{""border-radius: 10px;""background-color: #f1a8a8;""font-weight: bold;""}"
                             "QPushButton:hover {""background-color: #ed8c9f;""}"
                             "QPushButton:pressed {""background-color: #ed8c9f;""}"
                            );
    BotonAlto->setGeometry(850, 500, 120, 30);  // Ubicacion

    connect(BotonEj, &QPushButton::clicked, this, &MainWindow::Ejecutar);  // Conectar el clic del botón al slot Ejecutar
    connect(BotonAlto, &QPushButton::clicked, this, &MainWindow::ReiniciarTodo);  // Conectar el clic del botón al slot ReiniciarTodo
}

// Valida y guarda la ecuacion
void MainWindow::GuardaEcu(){
    QString Ecua = BarraE->text();

    QRegularExpression regex("^[0-9\\s\\+\\^\\-\\*/\\(\\)]+$"); // Esta expresión permite números y operadores
    QRegularExpressionMatch match = regex.match(Ecua);

    if (match.hasMatch()) { //match.hasMatch() verificar que una cadena contiene solo números y operadores designados
        // Si la ecuacion es valida
        GuardarE = Ecua;          // Guardar la ecuacion en la variable creada en .h
    } else {
        // Si la ecuacion no es valida
        if (Ecua== ""){
            // Error por no ingresar nada
            QMessageBox::warning(this, "Error", "No ingreso la ecuacion.");
        }else{
            // Error por no poner los signos correspondientes
            QMessageBox::warning(this, "Error", "La ecuación ingresada no es válida. Por favor, usa solo números y operadores básicos (+, -, ^, *, /, ()).");
        }
    }
}

// Funciones para validar las variables del minimo y el maximo
QString MainWindow::Confirmarm(){
    QString m = BarraMin->text();

    // Controla el texto de m
    QRegularExpression regex("^[0-9\\s\\-]+$");  // Esta expresión permite números y operadores
    QRegularExpressionMatch match = regex.match(m);

    if (match.hasMatch()) {
        // Si la ecuacion es valida
        return m;  // Transfiere la variable
    } else {
        if (m== ""){
            // Error por no ingresar nada
            QMessageBox::warning(this, "Error", "No ingreso el minimo.");
            return m;
        }else{
            // Error por no poner los signos correspondientes
            QMessageBox::warning(this, "Error", "Hay un problema en el minimo. Por favor, usa solo números positivos o negativos.");
        }
    }
}

QString MainWindow::ConfirmarM(){
    QString M = BarraMax->text();

    // Controla el texto de M
    QRegularExpression regex("^[0-9\\s\\-]+$");  // Esta expresión permite números y operadores
    QRegularExpressionMatch match = regex.match(M);

    if (match.hasMatch()) {
        // Si la ecuacion es valida
        return M;  // Transfiere la variable
    } else {
        if (M== ""){
            // Error por no ingresar nada
            QMessageBox::warning(this, "Error", "No ingreso el minimo.");
            return M;
        }else{
            // Error por no poner los signos correspondientes
            QMessageBox::warning(this, "Error", "Hay un problema en el minimo. Por favor, usa solo números positivos o negativos.");
        }
    }
}

// Funciones para guardar las variables del minimo y el maximo
void MainWindow::GuardarMm(){                                                                    
    QString m = Confirmarm();                                                                
    QString M = ConfirmarM();           
    if(m<M){
        // m siempre tiene que ser menor que que M
        Guardarm =m;   // Guardar la minimo en la variable de .h
        GuardarM =M;  // Guardar la maximo en la variable de .h
    }else{                                                                                 
        if(M==""||m==""){
            return;
        }else{
            // M es menor que m
            QMessageBox::warning(this, "Error", "Hay un problema en el maximo y el minimo. Por favor,el minimo no puede ser mayor o igual que el maximo.");
        }
    }                                                                                       
}
}

// Validacion y guardado de la variable de la subdivision
void MainWindow::GuardarSub(){
    QString Sub = BarraS->text();

    QRegularExpression regex("^[1-9][0-9]*$");  // Acepta números mayores que 0
    QRegularExpressionMatch match = regex.match(Sub);

    if (match.hasMatch()) { // Verifica que la cadena contiene solo números enteros positivos
        // Si el número es válido y mayor que 0
        GuardarS = Sub; // Guarda la subdivisión en la variable de .h
    } else {
        // Si el valor no es válido
        if (Sub == ""){
            // Error por no ingresar nada
            QMessageBox::warning(this, "Error", "No ingresó la subdivisión.");
        } else {
            // Error por ingresar un valor no permitido
            QMessageBox::warning(this, "Error", "La subdivisión debe ser un número entero mayor que 0.");
        }
    }
}

// Funcion del boton check
void MainWindow::Check(int state){
    if (state == Qt::Checked) {
        qDebug() << "Checkbox marcado";
    } else {
        qDebug() << "Checkbox desmarcado";
    }
}

// Funcion SLOT boton ejecutar
void MainWindow::Ejecutar() {
    // Validar y guardar la ecuación ingresada
    qDebug() << "Ejecutar() - Guardando ecuación...";
    GuardaEcu();

    // Validar y guardar la subdivisión
    qDebug() << "Ejecutar() - Guardando subdivisión...";
    GuardarSub();

    // Validar y guardar el mínimo y el máximo
    qDebug() << "Ejecutar() - Validar y guardando mínimo y máximo...";
    GuardarMm(m, M);

    qDebug() << "Ejecutar() - Fin de la función Ejecutar";
}


void MainWindow::ReiniciarTodo() {
    // Restablecer las variables
    GuardarE.clear();
    GuardarS.clear();
    Guardarm.clear();
    GuardarM.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
