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

// Ajusta el tamaño del viewport
void GraficoWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5, 10.5, -0.1, 1.1); // Configuración de las coordenadas
}

// Dibuja el contenido del widget
void GraficoWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxesWithLabels();    // Dibujar ejes
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
    glBegin(GL_LINES);

    // Eje X
    glColor3f(0.0f, 0.0f, 0.0f); // Negro
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(10.5f, 0.0f);

    // Eje Y
    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.0f, 1.1f);

    glEnd();

    // Dibujar etiquetas
    QPainter painter(this);
    painter.setPen(Qt::black);

    // Etiquetas del eje X
    for (int i = 0; i <= 10; ++i) {
        QString label = QString::number(i);
        painter.drawText(QPointF(i * width() / 10.0, height() / 2.0 - 10), label);
    }

    // Etiquetas del eje Y
    for (int i = 0; i <= 10; ++i) {
        QString label = QString::number(i / 10.0, 'f', 1);
        painter.drawText(QPointF(width() / 2.0 - 30, height() - i * height() / 10.0), label);
    }
}

// Dibuja los puntos de integración
void GraficoWidget::renderIntegrationPoints() {
    glColor3f(0.0f, 0.0f, 1.0f); // Azul para los puntos
    glPointSize(4.0f);

    glBegin(GL_POINTS);
    for (const auto& point : integrationPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}
