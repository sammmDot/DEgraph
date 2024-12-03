#ifndef GRAFICOWIDGET_H
#define GRAFICOWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPainter>
#include <vector>
#include <GL/glu.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>

// Estructura para almacenar puntos 2D
struct Point {
    float x, y;
};

class GraficoWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit GraficoWidget(QWidget* parent = nullptr);
    ~GraficoWidget();

protected:
    // Métodos principales de OpenGL
    void initializeGL() override;      // Inicialización de OpenGL
    void resizeGL(int w, int h) override;  // Ajuste de tamaño del viewport
    void paintGL() override;           // Renderizado del widget

private:
    // Métodos auxiliares
    void performIntegration();         // Realizar integración numérica
    void drawAxesWithLabels();         // Dibujar ejes y etiquetas
    void drawGrid();                   // Dibujar cuadrícula
    void renderIntegrationPoints();    // Dibujar los puntos de integración
    QPointF mapToWidgetCoords(float x, float y); // Convertir coordenadas gráficas a coordenadas del widget

    // Variables
    std::vector<Point> integrationPoints; // Puntos generados por la integración
};

#endif // GRAFICOWIDGET_H
