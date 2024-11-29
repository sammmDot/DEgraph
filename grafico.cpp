#include "grafico.h"
#include <QPainter>
#include <cmath>
#include <iostream>

Grafico::Grafico(QWidget* parent) : QOpenGLWidget(parent) {}

void Grafico::setPoints(const std::vector<Point>& points) {
    userPoints = points;
    update();  // Redibujar el widget
}

void Grafico::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Fondo blanco
    printf("hola");
}

void Grafico::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
}

void Grafico::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configurar cámara
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -30.0f);  // Alejar la cámara
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);  // Rotar en X
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);  // Rotar en Y

    // Dibujar elementos
    drawAxes();
    renderParametricCurve();
    renderQuadraticCurve();
    renderUserPoints();

    if (userPoints.size() >= 2) {
        renderDistanceBetweenPoints(userPoints[0], userPoints[1]);
    }
}

void Grafico::drawText(const QString& text, float x, float y, float z) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawText(x, y, text);
    painter.end();
}

void Grafico::drawAxes() {
    glBegin(GL_LINES);

    // Eje X
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    // Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Eje Z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();
}

void Grafico::renderParametricCurve() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (float t = -10; t < 10 * M_PI; t += 0.05) {
        float x = t * 0.5f;
        float y = sin(t);
        float z = cos(t);
        glVertex3f(x, y, z);
    }
    glEnd();
}

void Grafico::renderQuadraticCurve() {
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (float x = -10.0f; x <= 10.0f; x += 0.1f) {
        float y = x * x;
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
}

void Grafico::renderUserPoints() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (const auto& point : userPoints) {
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
}

void Grafico::renderDistanceBetweenPoints(const Point& p1, const Point& p2) {
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
}
