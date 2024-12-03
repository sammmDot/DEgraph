#ifndef GRAFICO_H
#define GRAFICO_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <QPointF>
#include <gsl/gsl_odeiv2.h>

class GraficoWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    GraficoWidget(QWidget* parent = nullptr);
    ~GraficoWidget();

    void setT(float newT) { GuardarM = newT; performIntegration(); update(); } // Actualiza t
    void setT1(float newT1) { Guardarm = newT1; performIntegration(); update(); } // Actualiza t1

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void performIntegration();
    void drawGrid();
    void drawAxesWithLabels();
    void renderIntegrationPoints();
    QPointF mapToWidgetCoords(float x, float y);

    std::vector<QPointF> integrationPoints;

    float GuardarM = 0.0f; // valor de t (min)
    float Guardarm = 10.0f; // valor de t1 (max)
};

#endif // GRAFICO_H
