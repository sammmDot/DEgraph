#include "grafico.h"
#include <QPainter>
#include <cmath>
#include <iostream>

Grafico::Grafico(QWidget* parent) : QOpenGLWidget(parent) {}

void Grafico::setPoints(const std::vector<Point>& points) {
    userPoints = points;
    update(); // Redibujar el widget
}

void Grafico::initializeGL() {
    initializeOpenGLFunctions();
    glDisable(GL_DEPTH_TEST); // Deshabilitar la profundidad porque es 2D
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fondo blanco
}

void Grafico::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = static_cast<float>(w) / h;

    // Rango para centrar la vista
    float rangeX = 100.0f * aspect;
    float rangeY = 100.0f;

    // Proyección ortográfica centrada
    glOrtho(-rangeX, rangeX, -rangeY, rangeY, -1.0, 1.0);
}

void Grafico::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar ejes y la curva cuadrática
    drawAxes();
    renderQuadraticCurve(); // Solo esta curva

    if (userPoints.size() >= 2) {
        renderDistanceBetweenPoints(userPoints[0], userPoints[1]);
    }
}

void Grafico::drawText(const QString& text, float x, float y) {
    QPainter painter(this);

    // Transformar coordenadas OpenGL a coordenadas de ventana
    QPointF screenPoint = mapFromGlobal(QPointF(x, y).toPoint());
    painter.setPen(Qt::black);
    painter.drawText(screenPoint, text);
    painter.end();
}

void Grafico::drawAxes() {
    // Dibujar ejes X e Y
    glBegin(GL_LINES);

    // Eje X (Rojo)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-100.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);

    // Eje Y (Verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, -100.0f);
    glVertex2f(0.0f, 100.0f);

    glEnd();

    // Dibujar números en los ejes usando QPainter
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 7));

    int w = width();   // Ancho de la ventana
    int h = height();  // Alto de la ventana

    // Transformación de coordenadas
    auto worldToScreen = [&](float x, float y) -> QPointF {
        float screenX = (x + 100) / 200.0f * w;
        float screenY = h - ((y + 100) / 200.0f * h); // OpenGL (abajo) a Qt (arriba)
        return QPointF(screenX, screenY);
    };

    // Números en el eje X
    for (int x = -100; x <= 100; x += 10) {
        if (x == 0) continue; // Saltar el origen
        QPointF screenPos = worldToScreen(x, -2); // Ajuste de altura (-2 para centrar)
        painter.drawText(screenPos, QString::number(x));
    }

    // Números en el eje Y
    for (int y = -100; y <= 100; y += 10) {
        if (y == 0) continue; // Saltar el origen
        QPointF screenPos = worldToScreen(-5, y); // Ajuste de ancho (-5 para centrar)
        painter.drawText(screenPos, QString::number(y));
    }

    painter.end();
}

void Grafico::renderQuadraticCurve() {
    // Dibuja la curva cuadrática
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo

    glBegin(GL_LINE_STRIP);
    for (float x = -100.0f; x <= 100.0f; x += 0.1f) {
        float y = 0.01f * x * x;  // y = x^2
        glVertex2f(x, y);
    }
    glEnd();
}

void Grafico::renderDistanceBetweenPoints(const Point& p1, const Point& p2) {
    float distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    QString text = QString("Distancia: %1").arg(distance);
    drawText(text, (p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
}
