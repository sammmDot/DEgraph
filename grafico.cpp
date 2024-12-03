#include "grafico.h"
#include <QPainter>
#include <cmath>
#include <string>

// Constructor
GraficoWidget::GraficoWidget(QWidget* parent)
    : QOpenGLWidget(parent) {}

// Destructor
GraficoWidget::~GraficoWidget() {}

// Inicializa OpenGL
void GraficoWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fondo blanco

    performIntegration(); // Realizar integración al iniciar
}

// Ajusta el tamaño del viewport y define la proyección
void GraficoWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 11.0, -0.2, 1.2, -1.0, 1.0); // Ampliar un poco los márgenes
}

// Dibuja el contenido del widget
void GraficoWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();              // Dibujar cuadrícula
    drawAxesWithLabels();    // Dibujar ejes y etiquetas
    renderIntegrationPoints(); // Dibujar puntos
}

// Realiza la integración numérica
void GraficoWidget::performIntegration() {
    gsl_odeiv2_system sys = {
        [](double t, const double y[], double dydt[], void*) -> int {
            dydt[0] = std::sin(t) - y[0];
            return GSL_SUCCESS;
        },
        nullptr, 1, nullptr
    };

    const gsl_odeiv2_step_type* T = gsl_odeiv2_step_rkf45;
    gsl_odeiv2_driver* d = gsl_odeiv2_driver_alloc_y_new(&sys, T, 0.1, 1e-6, 1e-6);

    double y[1] = {1.0};
    double t = 0.0;
    double t1 = 10.0;
    int num_points = 1000;
    double dt = t1 / (num_points - 1);

    for (int i = 0; i < num_points; i++) {
        double t_actual = i * dt;
        gsl_odeiv2_driver_apply(d, &t, t_actual, y);
        integrationPoints.push_back({static_cast<float>(t), static_cast<float>(y[0])});
    }

    gsl_odeiv2_driver_free(d);
}

// Dibuja los ejes y sus etiquetas
void GraficoWidget::drawAxesWithLabels() {
    glColor3f(0.0f, 0.0f, 0.0f); // Negro para los ejes
    glLineWidth(2.0f);

    // Dibujar ejes X y Y
    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.1f); glVertex2f(0.0f, 1.1f); // Eje Y
    glVertex2f(-0.5f, 0.0f); glVertex2f(10.5f, 0.0f); // Eje X
    glEnd();

    // Usar QPainter para etiquetas
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));

    // Etiquetas del eje X
    for (int i = 0; i <= 10; ++i) {
        QString label = QString::number(i);
        QPointF pos = mapToWidgetCoords(i, -0.05f);
        painter.drawText(pos, label);
    }

    // Etiquetas del eje Y
    for (int i = 0; i <= 10; ++i) {
        QString label = QString::number(i / 10.0, 'f', 1);
        QPointF pos = mapToWidgetCoords(-0.3f, i / 10.0f);
        painter.drawText(pos, label);
    }
}

// Dibuja la cuadrícula
void GraficoWidget::drawGrid() {
    glColor3f(0.9f, 0.9f, 0.9f); // Gris claro para la cuadrícula
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    // Líneas verticales (X)
    for (int i = 0; i <= 10; ++i) {
        glVertex2f(i, -0.1f);
        glVertex2f(i, 1.1f);
    }

    // Líneas horizontales (Y)
    for (int i = 0; i <= 10; ++i) {
        float y = i / 10.0f;
        glVertex2f(-0.5f, y);
        glVertex2f(10.5f, y);
    }

    glEnd();
}

// Dibuja los puntos de integración
void GraficoWidget::renderIntegrationPoints() {
    glColor3f(0.0f, 0.0f, 1.0f); // Azul para los puntos
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    for (const auto& point : integrationPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

// Convierte coordenadas del gráfico a coordenadas del widget
QPointF GraficoWidget::mapToWidgetCoords(float x, float y) {
    float widgetX = (x + 0.5f) * width() / 11.0f;
    float widgetY = height() - (y + 0.1f) * height() / 1.3f;
    return QPointF(widgetX, widgetY);
}
