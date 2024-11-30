#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMap>
#include <QMessageBox>          // Aparece otra ventan con un mensaje
#include <QRegularExpression>   // Verifica el formato de entradas de usuario, extraer información de texto o validar datos
#include <QDebug>

#include <muParser.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>

mu::Parser parser;

int EDO(double t, const double y[], double dydt[], void *params) {
    try {
        // Configurar las variables del parser
        parser.DefineVar("t", &t);
        parser.DefineVar("y", const_cast<double*>(&y[0]));  // muParser necesita un puntero no constante

        // Evaluar la ecuación almacenada en GuardarE
        dydt[0] = parser.Eval();
        return GSL_SUCCESS;
    } catch (mu::Parser::exception_type &e) {
        qCritical() << "Error en el parser:" << QString::fromStdString(e.GetMsg());
        return GSL_EBADFUNC;
    }
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    // Texto
    Titulo = new QLabel(this);
    QPixmap pixmap(":/logo/Logo.png");// Cargar la imagen desde un archivo
    Titulo->setPixmap(pixmap);
    Titulo->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));  // Ajustar imagen al QLabel
    Titulo->setGeometry(675, 40, 500, 150); // Usar geometría para establecer posición y tamaño

    tituloE = new QLabel("Ingrese la ecuacion:", this);
    tituloE->setGeometry(700, 180, 200, 20); // Posición (x, y) y tamaño ancho x alto
    tituloE->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    tituloMin = new QLabel("Minimo:", this);
    tituloMin->setGeometry(700, 280, 100, 20); // Posición (x, y) y tamaño ancho x alto
    tituloMin->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;");

    tituloMax = new QLabel("Maximo:", this);
    tituloMax->setGeometry(850, 280, 100, 20); // Posición (x, y) y tamaño ancho x alto
    tituloMax->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    tituloS = new QLabel("Subdivision:", this);
    tituloS->setGeometry(700, 380, 250, 20); // Posición (x, y) y tamaño ancho x alto
    tituloS->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    tituloC = new QLabel("Eje z", this);
    tituloC->setGeometry(734, 505, 250, 20); // Posición (x, y) y tamaño ancho x alto
    tituloC->setStyleSheet("font-size: 12px; font-weight: bold; color: #333;"); // Caracteristicas generales

    // Botones ayuda
    BotonAE = new QPushButton("i", this);
    // Caracteristicas del boton
    BotonAE->setStyleSheet("QPushButton {""border-radius: 7px;""background-color: #d3d3d3;""font-weight: bold;""color: #2c2c2c;""}"
                           "QPushButton:hover {""background-color: #c0c0c0;""}"
                           "QPushButton:pressed {""background-color: #c0c0c0;""}");
    BotonAE->setGeometry(910, 205, 18, 18);  // Ubicacion
    // Conectar el clic del botón al slot, aparece una ventana emergente con na pequeña descripcion
    connect(BotonAE, &QPushButton::clicked, this, &MainWindow::BAE);

    BotonAMm = new QPushButton("i", this);
    // Caracteristicas del boton
    BotonAMm->setStyleSheet("QPushButton {""border-radius: 7px;""background-color: #d3d3d3;""font-weight: bold;""color: #2c2c2c;""}"
                           "QPushButton:hover {""background-color: #c0c0c0;""}"
                           "QPushButton:pressed {""background-color: #c0c0c0;""}");
    BotonAMm->setGeometry(815, 305, 18, 18);  // Ubicacion
    // Conectar el clic del botón al slot, aparece una ventana emergente con na pequeña descripcion
    connect(BotonAMm, &QPushButton::clicked, this, &MainWindow::BAMm);

    BotonAS = new QPushButton("i", this);
    // Caracteristicas del boton
    BotonAS->setStyleSheet("QPushButton {""border-radius: 7px;""background-color: #d3d3d3;""font-weight: bold;""color: #2c2c2c;""}"
                           "QPushButton:hover {""background-color: #c0c0c0;""}"
                           "QPushButton:pressed {""background-color: #c0c0c0;""}");
    BotonAS->setGeometry(910, 405, 18, 18);  // Ubicacion
    // Conectar el clic del botón al slot, aparece una ventana emergente con na pequeña descripcion
    connect(BotonAS, &QPushButton::clicked, this, &MainWindow::BAS);

    BotonAZ = new QPushButton("i", this);
    // Caracteristicas del boton
    BotonAZ->setStyleSheet("QPushButton {""border-radius: 7px;""background-color: #d3d3d3;""font-weight: bold;""color: #2c2c2c;""}"
                            "QPushButton:hover {""background-color: #c0c0c0;""}"
                            "QPushButton:pressed {""background-color: #c0c0c0;""}");
    BotonAZ->setGeometry(770, 505, 18, 18);  // Ubicacion
    // Conectar el clic del botón al slot, aparece una ventana emergente con na pequeña descripcion
    connect(BotonAZ, &QPushButton::clicked, this, &MainWindow::BAZ);



    // Funcion para barra de ecuaciones
    Autocompletar();

    // Intput minimo
    BarraMin = new QLineEdit(this);             // Crea la barra de texto
    //Caracterristicas de la barra
    BarraMin->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #b4ddd8;"
                            "}");
    BarraMin->setGeometry(700, 300, 100, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra


    // Imput maximo
    BarraMax = new QLineEdit(this);              // Crea la barra de texto
    //Caracterristicas de la barra
    BarraMax->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #b4ddd8;"
                            "}");
    BarraMax->setGeometry(850, 300, 100, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Imput subdivision
    BarraS = new QLineEdit(this);              // Crea la barra de texto
    //Caracterristicas de la barra
    BarraS->setStyleSheet("QLineEdit {"
                            "border-radius: 10px;"
                            "padding: 5px;"
                            "background-color: #b4ddd8;"
                            "}");
    BarraS->setGeometry(700, 400, 200, 30);    // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra

    // Boton check
    BotonC = new QCheckBox(this);
    BotonC->setGeometry(710, 500, 15, 30); // Posición y tamaño de check
    connect(BotonC, &QCheckBox::stateChanged, this, &MainWindow::Check);  //conecta el boton con una condicion

    // Boton ejecutar
    BotonEj = new QPushButton("Ejecutar", this);
        // Caracteristicas del boton
    BotonEj->setStyleSheet("QPushButton{""border-radius: 10px;""background-color: #bef2af;""font-weight: bold;""}"
                           "QPushButton:hover {""background-color: #8aeb81;""}"
                           "QPushButton:pressed {""background-color: #8aeb81;""}"
                           );
    BotonEj->setGeometry(700, 600, 100, 50);  // Ubicacion
    connect(BotonEj, &QPushButton::clicked, this, &MainWindow::Ejecutar);  // Conectar el clic del botón al slot Ejecutar

    // Boton detener
    BotonAlto = new QPushButton("Detener", this);
        // Caracteristicas del boton
    BotonAlto->setStyleSheet("QPushButton{""border-radius: 10px;""background-color: #f1a8a8;""font-weight: bold;""}"
                             "QPushButton:hover {""background-color: #ed8c9f;""}"
                             "QPushButton:pressed {""background-color: #ed8c9f;""}"
                            );
    BotonAlto->setGeometry(850, 600, 100, 50);  // Ubicacion

    connect(BotonAlto, &QPushButton::clicked, this, &MainWindow::ReiniciarTodo);  // Conectar el clic del botón al slot ReiniciarTodo

    // Boton glosario
    BotonGlo = new QPushButton(this);
        // Caracteristicas del boton
    BotonGlo->setStyleSheet("QPushButton {"
                            "border-radius: 10px; "
                            "icon-size: 50px 50px;"                     // Tamaño del ícono
                            "background-color: #b4ddd8;"                 // Color de fondo
                            "qproperty-icon: url(:/botones/boton.png);" // Imagen normal
                            "}"
                            "QPushButton:hover {"
                            "background-color: #a8dbd4;"                       // Color de fondo
                            "qproperty-icon: url(:/botones/boton_pres.png);"  // Imagen en hover
                            "}"
                            "QPushButton:pressed {"
                            "background-color: #a8dbd4;"                      // Color de fondo
                            "qproperty-icon: url(:/botones/boton_pres.png);"  // Imagen en hover
                            "}"
                            );
    BotonGlo->setGeometry(870, 485, 60, 60);  // Ubicacion
    connect(BotonGlo, &QPushButton::clicked, this, &MainWindow::Glosario);   // Conectar el clic del botón al slot Glosario, abiendo otra vetana
}

// Botones de ayuda
void MainWindow::BAE(){
    QMessageBox::information(this, " ", "La ecuacion debe tene almenos un numero o varable(x ,y o z). Ademas se pueden agregar funciones, las cuales estan disponibles en el boton con un libro, indicandole que hace cada una.");
}
void MainWindow::BAMm(){
    QMessageBox::information(this, " ", "Esto indica elrango donde se mvera la funcion en el eje y.");//no estoy segura de esto
}
void MainWindow::BAS(){
    QMessageBox::information(this, " ", "Divide las lineas????");
}
void MainWindow::BAZ(){
    QMessageBox::information(this, " ", "Si el check esta activado, este mostrara un grafico con trs ejes, ose que sera de tres dimenciones. En cambio, si esta desactivado, el grafico solo mostrara dos eje, siendo asi de dos dimensiones");
}


// Valida y guarda la ecuacion
void MainWindow::Autocompletar()
{
    //lista de comandos para las funciones matematicas de la bibloteca cmat
    QStringList commands = {"sin()", "cos()", "tan()", "asin()", "acos()", "atan()", "atan2()",
                            "sinh()", "cosh()", "tanh()", "asinh()", "acosh()", "atanh()", "exp()",
                            "log()", "log10()", "log2()", "pow()", "sqrt()", "floor()", "round()"
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
                            "background-color: #b4ddd8;"
                            "}");
    BarraE->setGeometry(700, 200, 200, 30);   // Los dos primeros lo ubican en el plano, el tercero es el largo y el ultimo el ancho de la barra
    BarraE->setCompleter(completar);
}

void MainWindow::GuardaEcu() {
    QString Ecua = BarraE->text().trimmed();

    // Expresión regular para validar la ecuación
    QRegularExpression regex("^\\s*([\\dx+yz\\-*/^()\\s]+|(\\b(?:sin|cos|tan|asin|acos|atan|atan2|sinh|cosh|tanh|asinh|acosh|atanh|exp|log|log10|log2|pow|sqrt|floor|round|copysign)\\b\\s*\\(\\s*[\\dx+yz\\-*/^()\\s]+\\)))+$");
    QRegularExpressionMatch match = regex.match(Ecua);

    // Verificar que contenga al menos un número o variable (x, y, z)
    bool contieneNumero = Ecua.contains(QRegularExpression("[\\dxyz]"));

    if (match.hasMatch() && contieneNumero) {
        try {
            // Inicializa el parser de muParser
            double y_value = 0.0;
            parser.DefineVar("y", &y_value);

            // Agrega constantes matemáticas
            parser.DefineConst("pi", M_PI);
            parser.DefineConst("e", M_E);

            // Convierte QString a std::string para SetExpr
            parser.SetExpr(Ecua.toStdString());

            // Si la ecuación es válida, guarda en GuardarE
            qDebug() << "Ecuación: " << GuardarE;
            GuardarE = Ecua; // Si GuardarE es QString
            qDebug() << "Ecuación: " << GuardarE;

            // Cambiar estilo del QLineEdit
            BarraE->setStyleSheet("QLineEdit {"
                                  "border-radius: 10px;"
                                  "padding: 5px;"
                                  "background-color: #b4ddd8;"
                                  "}");
        } catch (mu::ParserError &e) {
            // Si ocurre un error en muParser
            QMessageBox::warning(this, "Error", QString("Error en la ecuación: %1").arg(e.GetMsg().c_str()));
            BarraE->setStyleSheet("QLineEdit {"
                                  "border-radius: 10px;"
                                  "padding: 5px;"
                                  "background-color: #f5c2bd;"
                                  "}");
        }
    } else {
        // Ecuación no válida
        if (Ecua.isEmpty()) {
            QMessageBox::warning(this, "Error", "No ingresó la ecuación.");
        } else {
            // QMessageBox::warning(this, "Error", "La ecuación ingresada no es válida.");
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
        if (min < max) {
            Guardarm = min;   // Guardar mínimo
            GuardarM = max;   // Guardar máximo
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
        bool conversionOk;
        GuardarS = Sub.toFloat(&conversionOk);  // Guarda la subdivisión en la variable de .h
        BarraS->setStyleSheet("QLineEdit {"
                                "border-radius: 10px;"
                                "padding: 5px;"
                                "background-color: #b4ddd8;"
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
    try {
        // Guardar la ecuación y los parámetros necesarios
        qDebug() << "Ejecutar() - Configurando ecuación...";
        GuardaEcu();  // Guardar la ecuación en GuardarE

        qDebug() << "Ejecutar() - Guardando mínimo y máximo...";
        GuardarMm();  // Guardar los valores mínimo y máximo

        qDebug() << "Ejecutar() - Configurando subdivisión...";
        GuardarSub();  // Guardar subdivisión si es necesario

        // Configurar el parser con la ecuación ingresada
        parser.SetExpr(GuardarE.toStdString());  // Convertir QString a std::string

        // Establecer el sistema de ecuaciones a resolver
        gsl_odeiv2_system sys = {EDO, NULL, 1, NULL};

        // Inicializar el contexto de la integración
        gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(
            &sys,
            gsl_odeiv2_step_rk8pd,  // Método de Runge-Kutta de 8° orden
            1e-6,  // Precisión de la integración
            1e-6,  // Precisión relativa
            0.0    // Tolerancia absoluta
            );

        // Inicializar el valor de y (condición inicial)
        double y[1] = {1.0};  // Ejemplo: valor inicial para y(Guardarm)

        // Establecer el tiempo inicial y final
        double t = Guardarm;
        double t_final = GuardarM;

        // Realizar la integración
        while (t < t_final) {
            // Realizar un paso de integración
            int status = gsl_odeiv2_driver_apply(driver, &t, t + 1.0, y);  // Incrementar por 1 segundo

            // Verificar si ocurrió algún error
            if (status != GSL_SUCCESS) {
                throw std::runtime_error("Error en la integración");
            }

            // Mostrar el valor de y(t) en este paso de tiempo
            qDebug() << "Tiempo: " << t << " Valor de y: " << y[0];
        }

        // Liberar el contexto del driver después de la integración
        gsl_odeiv2_driver_free(driver);

        qDebug() << "Integración terminada";

    } catch (const std::exception &e) {
        // Mostrar mensaje de error si ocurre alguna excepción
        QMessageBox::critical(this, "Error crítico", QString("Ocurrió un error inesperado: %1").arg(e.what()));
    } catch (mu::Parser::exception_type &e) {
        // Mostrar mensaje de error específico del parser
        QMessageBox::critical(this, "Error en ecuación", QString("Error al procesar la ecuación: %1").arg(e.GetMsg().c_str()));
    }
}


// Funcion SLOT boton Detener
void MainWindow::ReiniciarTodo() {
    // Restablecer las variables
    BarraE->setStyleSheet("QLineEdit {"
                          "border-radius: 10px;"
                          "padding: 5px;"
                          "background-color: #b4ddd8;"
                          "}");
    BarraS->setStyleSheet("QLineEdit {"
                          "border-radius: 10px;"
                          "padding: 5px;"
                          "background-color: #b4ddd8;"
                          "}");
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
}


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
    this->resize(300, 300);

    // Etiqueta para título
    Glo = new QLabel("Selecciona una función para ver la descripción:", this);
    Glo->setAlignment(Qt::AlignCenter);

    // Layout principal
    G = new QVBoxLayout();
    G->addWidget(Glo);

    // Lista de funciones
    listG = new QListWidget(this);
    QMap<QString, QString> glossary = crearGlosario();

    for (const QString &functionName : glossary.keys()) {
        QListWidgetItem *item = new QListWidgetItem(functionName, listG);
        item->setData(Qt::UserRole, glossary.value(functionName)); // Guardar descripción en el item
    }

    // Añadir la lista al layout
    G->addWidget(listG);

    // Etiqueta para mostrar la descripción
    descriptionLabel = new QLabel("Descripción: ", this);
    descriptionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    descriptionLabel->setWordWrap(true); // Permitir que el texto se ajuste al ancho del widget
    G->addWidget(descriptionLabel);

    // Conectar la selección de la lista al cambio de texto en la etiqueta
    connect(listG, &QListWidget::itemClicked, this, &SecondWindow::mostrarDescripcion);

    // Aplicar el layout principal
    this->setLayout(G);
}

// Método para mostrar la descripción en el QLabel
void SecondWindow::mostrarDescripcion(QListWidgetItem *item) {
    QString description = item->data(Qt::UserRole).toString();
    descriptionLabel->setText("Descripción: " + description);
}

MainWindow::~MainWindow() {}

SecondWindow::~SecondWindow() {}

