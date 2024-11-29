#ifndef GRAFICO_H
#define GRAFICO_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <string>

struct Point {
    float x, y, z;
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
    void drawText(const QString& text, float x, float y, float z);
    void drawAxes();
    void renderParametricCurve();
    void renderQuadraticCurve();
    void renderUserPoints();
    void renderDistanceBetweenPoints(const Point& p1, const Point& p2);
};

#endif // GRAFICO_H
