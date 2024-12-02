#ifndef GRAFICO_H
#define GRAFICO_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <QString>

// Estructura para representar un punto en 2D
struct Point {
    float x, y;
};

class Grafico : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit Grafico(QWidget* parent = nullptr);
    void setPoints(const std::vector<Point>& points);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::vector<Point> userPoints;

    void drawText(const QString& text, float x, float y);
    void drawAxes();
    void renderQuadraticCurve(); // Mantener solo la curva cuadrática
    void renderDistanceBetweenPoints(const Point& p1, const Point& p2);
};

#endif // GRAFICO_H
