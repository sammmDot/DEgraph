#ifndef GRAFICOWIDGET_H
#define GRAFICOWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>

#include <GL/glu.h>
#include <muParser.h>
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
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    // Métodos auxiliares
    void performIntegration(); // Realizar la integración
    void drawAxesWithLabels(); // Dibujar los ejes
    void renderIntegrationPoints(); // Dibujar los puntos

    // Variables
    std::vector<Point> integrationPoints; // Puntos generados por la integración
};

#endif // GRAFICOWIDGET_H
