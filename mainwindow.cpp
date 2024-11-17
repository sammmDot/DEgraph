#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMap>
#include <QMessageBox>          // Aparece otra ventan con un mensaje
#include <QRegularExpression>   // Verifica el formato de entradas de usuario, extraer información de texto o validar datos


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    // Texto
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

    tituloC = new QLabel("Eje z", this);
    tituloC->setGeometry(740, 405, 250, 20); // Posición (x, y) y tamaño ancho x alto
    tituloC->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    // Funcion para barra de ecuaciones
    Autocompletar();

    // Intput minimo
    BarraMin = new QLineEdit(this);             // Crea la barra de texto
    //Caracterristicas de la barra
    BarraMin->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #dcfaf0;"
                            "}");
    BarraMin->setGeometry(700, 200, 100, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra


    // Imput maximo
    BarraMax = new QLineEdit(this);              // Crea la barra de texto
    //Caracterristicas de la barra
    BarraMax->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #dcfaf0;"
                            "}");
    BarraMax->setGeometry(850, 200, 100, 30);    // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Imput subdivision
    BarraS = new QLineEdit(this);              // Crea la barra de texto
    //Caracterristicas de la barra
    BarraS->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #dcfaf0;"
                            "}");
    BarraS->setGeometry(700, 300, 250, 30);    // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Boton check
    BotonC = new QCheckBox(this);
    BotonC->setGeometry(720, 400, 200, 30); // Posición y tamaño de check
    connect(BotonC, &QCheckBox::stateChanged, this, &MainWindow::Check);  //conecta el boton con una condicion

    // Boton ejecutar
    BotonEj = new QPushButton("Ejecutar", this);
        // Caracteristicas del boton
    BotonEj->setStyleSheet("QPushButton{""border-radius: 10px;""background-color: #bef2af;""font-weight: bold;""}"
                           "QPushButton:hover {""background-color: #8aeb81;""}"
                           "QPushButton:pressed {""background-color: #8aeb81;""}"
                           );
    BotonEj->setGeometry(700, 500, 100, 50);  // Ubicacion
    connect(BotonEj, &QPushButton::clicked, this, &MainWindow::Ejecutar);  // Conectar el clic del botón al slot Ejecutar

    // Boton detener
    BotonAlto = new QPushButton("Detener", this);
        // Caracteristicas del boton
    BotonAlto->setStyleSheet("QPushButton{""border-radius: 10px;""background-color: #f1a8a8;""font-weight: bold;""}"
                             "QPushButton:hover {""background-color: #ed8c9f;""}"
                             "QPushButton:pressed {""background-color: #ed8c9f;""}"
                            );
    BotonAlto->setGeometry(850, 500, 100, 50);  // Ubicacion

    connect(BotonAlto, &QPushButton::clicked, this, &MainWindow::ReiniciarTodo);  // Conectar el clic del botón al slot ReiniciarTodo

    // Boton glosario
    BotonGlo = new QPushButton(this);
        // Caracteristicas del boton
    BotonGlo->setStyleSheet("QPushButton {"
                            "border-radius: 10px; "
                            "icon-size: 50px 50px;"                     // Tamaño del ícono
                            "background-color: #dcfaf0;"                 // Color de fondo
                            "qproperty-icon: url(:/botones/boton.png);" // Imagen normal
                            "}"
                            "QPushButton:hover {"
                            "background-color: #c3f4e3;"                // Color de fondo
                            "qproperty-icon: url(:/botones/boton_pres.png);"  // Imagen en hover
                            "}"
                            "QPushButton:pressed {"
                            "background-color: #c3f4e3;"                      // Color de fondo
                            "qproperty-icon: url(:/botones/boton_pres.png);"  // Imagen en hover
                            "}"
                            );
    BotonGlo->setGeometry(870, 385, 60, 60);  // Ubicacion
    connect(BotonGlo, &QPushButton::clicked, this, &MainWindow::Glosario);   // Conectar el clic del botón al slot Glosario, abiendo otra vetana
}


// Valida y guarda la ecuacion
void MainWindow::Autocompletar()
{
    //lista de comandos para las funciones matematicas de la bibloteca cmat
    QStringList commands = {"sin()", "cos()", "tan()", "asin()", "acos()", "atan()", "atan2()",
                            "sinh()", "cosh()", "tanh()", "asinh()", "acosh()", "atanh()",
                            "exp()", "log()", "log10()", "log2()", "pow()", "sqrt()", "cbrt()",
                            "ceil", "floor", "trunc", "round", "nearbyint", "remainder",
                            "fmod()", "fmax()", "fmin()", "fabs()", "hypot()", "frexp()", "ldexp()",
                            "modf()", "copysign()"
    };

    // Crear el modelo para el autocompletar con la lista de comandos
    model = new QStringListModel(commands, this);

    // Configurar el completador
    completar = new QCompleter(model, this);                         // Use una lista de comandos (commands) para autocompletar.
    completar->setCaseSensitivity(Qt::CaseInsensitive);              // Ignore mayúsculas y minúsculas en las coincidencias.
    completar->setCompletionMode(QCompleter::InlineCompletion);      // Sugiera palabras directamente en el campo de texto mientras el usuario escribe.

    // Intput ecuaciones
    BarraE = new QLineEdit(this);             // Crea la barra de texto
    //Caracterristicas de la barra
    BarraE->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #dcfaf0;"
                            "}");
    BarraE->setGeometry(700, 100, 250, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra
    BarraE->setCompleter(completar);
}

void MainWindow::GuardaEcu() {
    QString Ecua = BarraE->text();

    QRegularExpression regex("^\\s*([\\dx+yz\\-*/^()\\s]+|(\\b(?:sin|cos|tan|asin|acos|atan|atan2|sinh|cosh|tanh|asinh|acosh|atanh|exp|log|log10|log2|pow|sqrt|cbrt|ceil|floor|trunc|round|nearbyint|remainder|fmod|fmax|fmin|fabs|hypot|frexp|ldexp|modf|copysign)\\b\\s*\\(\\s*[\\dx+yz\\-*/^()\\s]+\\)))+$"); // Incluye x, y, z y al menos un número
    QRegularExpressionMatch match = regex.match(Ecua);

    // Verificar que contenga al menos un número o variable (x, y, z)
    bool contieneNumero = Ecua.contains(QRegularExpression("[\\dxyz]"));

    if (match.hasMatch() && contieneNumero) { // Verifica que contenga solo caracteres válidos y al menos un número
        // Si la ecuación es válida
        BarraE->setStyleSheet("QLineEdit {"
                              "border-radius: 10px;"
                              "padding: 5px;"
                              "background-color: #dcfaf0;"
                              "}");
        GuardarE = Ecua;  // Guardar la ecuación en la variable creada en .h
    } else {
        // La ecuación no es válida
        if (Ecua.isEmpty()) {
            QMessageBox::warning(this, "Error", "No ingresó la ecuación.");
        } else {
            QMessageBox::warning(this, "Error", "La ecuación ingresada no es válida. Por favor, usa solo números, operadores básicos, variables (x, y, z), y funciones válidas como sin(), cos(), etc(Las puedes encontrar en el glosario).");
        }
        BarraE->setStyleSheet("QLineEdit {"
                              "border-radius: 10px;"
                              "padding: 5px;"
                              "background-color: #f5c2bd;"
                              "}");
    }
}


// Funciones para validar las variables del minimo y el maximo
QString MainWindow::Confirmarm(){
    QString m = BarraMin->text();

    bool conversionOk;
    double minValue = m.toDouble(&conversionOk);  // Intenta convertir m a número

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
                            "background-color: #dcfaf0;"
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
                            "background-color: #dcfaf0;"
                            "}");
    return M;  // Devuelve el valor si es válido
}

void MainWindow::GuardarMm(){
    QString m = Confirmarm();
    QString M = ConfirmarM();

    if (m.isEmpty() || M.isEmpty()) {
        return;  // Termina la función si hubo error previo en m o M
    }

    // Conversión segura, dado que m y M son válidos
    bool conversionOk1, conversionOk2;
    double minValue = m.toDouble(&conversionOk1);
    double maxValue = M.toDouble(&conversionOk2);

    if (conversionOk1 && conversionOk2) {
        if (minValue < maxValue) {
            Guardarm = m;   // Guardar mínimo
            GuardarM = M;   // Guardar máximo
            BarraMin->setStyleSheet("QLineEdit {"
                                    "border-radius: 10px;"
                                    "padding: 5px;"
                                    "background-color: #dcfaf0;"
                                    "}");
            BarraMax->setStyleSheet("QLineEdit {"
                                    "border-radius: 10px;"
                                    "padding: 5px;"
                                    "background-color: #dcfaf0;"
                                    "}");
        } else {
            QMessageBox::warning(this, "Error", "El mínimo no puede ser mayor o igual que el máximo.");
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
        BarraS->setStyleSheet("QLineEdit {"
                                "border-radius: 10px;"
                                "padding: 5px;"
                                "background-color: #dcfaf0;"
                                "}");
    } else {
        // Si el valor no es válido
        if (Sub == ""){
            // Error por no ingresar nada
            QMessageBox::warning(this, "Error", "No ingresó la subdivisión.");
        } else {
            // Error por ingresar un valor no permitido
            QMessageBox::warning(this, "Error", "La subdivisión debe ser un número entero mayor que 0.");
        }
        BarraS->setStyleSheet("QLineEdit {"
                              "border-radius: 10px;"
                              "padding: 5px;"
                              "background-color: #f5c2bd;"
                              "}");
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
    try{
        // Validar y guardar la ecuación ingresada
        qDebug() << "Ejecutar() - Guardando ecuación...";
        GuardaEcu();

        // Validar y guardar el mínimo y el máximo
        qDebug() << "Ejecutar() - Guardando mínimo y máximo...";
        GuardarMm();

        // Validar y guardar la subdivisión
        qDebug() << "Ejecutar() - Guardando subdivisión...";
        GuardarSub();

        qDebug() << "Ejecutar() - Fin de la función Ejecutar";
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error crítico", QString("Ocurrió un error inesperado: %1").arg(e.what()));
    }
}


// Funcion SLOT boton Detener
void MainWindow::ReiniciarTodo() {
    // Restablecer las variables
    GuardarE.clear();
    BarraE->setStyleSheet("QLineEdit {"
                          "border-radius: 10px;"
                          "padding: 5px;"
                          "background-color: #dcfaf0;"
                          "}");
    GuardarS.clear();
    BarraS->setStyleSheet("QLineEdit {"
                          "border-radius: 10px;"
                          "padding: 5px;"
                          "background-color: #dcfaf0;"
                          "}");
    Guardarm.clear();
    BarraMin->setStyleSheet("QLineEdit {"
                          "border-radius: 10px;"
                          "padding: 5px;"
                          "background-color: #dcfaf0;"
                          "}");
    GuardarM.clear();
    BarraMax->setStyleSheet("QLineEdit {"
                          "border-radius: 10px;"
                          "padding: 5px;"
                          "background-color: #dcfaf0;"
                          "}");
}

MainWindow::~MainWindow() {}



// Datos del glosario (nombre de la función y descripción)
QMap<QString, QString> crearGlosario() {
    QMap<QString, QString> glossary;
    glossary["abs"] = "Devuelve el valor absoluto de un número.";
    glossary["acos"] = "Devuelve el arco coseno de un valor en radianes.";
    glossary["asin"] = "Devuelve el arco seno de un valor en radianes.";
    glossary["atan"] = "Devuelve el arco tangente de un valor en radianes.";
    glossary["cos"] = "Devuelve el coseno de un ángulo (en radianes).";
    glossary["sin"] = "Devuelve el seno de un ángulo (en radianes).";
    glossary["tan"] = "Devuelve la tangente de un ángulo (en radianes).";
    glossary["sqrt"] = "Devuelve la raíz cuadrada de un número.";
    glossary["log"] = "Devuelve el logaritmo natural (base e) de un número.";
    glossary["pow"] = "Eleva un número base a una potencia específica.";
    return glossary;
}

// Función para abrir la segunda ventana
void MainWindow::Glosario() {
    SecondWindow *newWindow = new SecondWindow();
    newWindow->show();
}

// Implementación de SecondWindow
SecondWindow::SecondWindow(QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("Glosario de funciones");
    this->resize(300, 200);

    Glo = new QLabel("Selecciona una función para ver la descripción:", this);
    Glo->setAlignment(Qt::AlignCenter);

    G = new QVBoxLayout();
    G->addWidget(Glo);
    this->setLayout(G);

    // Crear lista de funciones con sus descripciones
    listG = new QListWidget(this);
    QMap<QString, QString> glossary = crearGlosario();

    // Verifica si el glosario se está creando correctamente
    qDebug() << "Glosario creado con " << glossary.size() << " elementos.";

    for (const QString &functionName : glossary.keys()) {
        QListWidgetItem *item = new QListWidgetItem(functionName, listG);
        QString tooltipText = glossary.value(functionName);

        // Debugging: verifica que los tooltips estén configurados correctamente
        qDebug() << "Asignando tooltip: " << tooltipText;

        item->setToolTip(tooltipText); // Mostrar la descripción al pasar el ratón
    }

    // Añadir la lista al layout
    G->addWidget(listG);
    listG->setFocus();

    // Estilo de los tooltips (en caso de que no se muestren con el estilo por defecto)
    qApp->setStyleSheet("QToolTip { "
                        "color: #ffffff; "
                        "background-color: #2a82da; "
                        "border: 1px solid #000000; "
                        "padding: 5px; "
                        "border-radius: 3px; }");

    this->setLayout(G);
}

SecondWindow::~SecondWindow() {}




















MainWindow::~MainWindow()
{
    delete ui;
}

