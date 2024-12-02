#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>
#include <cmath>
#include <vector>
#include <iostream>

// Estructura para almacenar puntos 2D
struct Point {
    float x, y;
};

std::vector<Point> integrationPoints;  // Puntos generados por la integración

// Función para dibujar texto en coordenadas 2D
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

// Configuración del viewport y la cámara
void setupViewport(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5, 10.5, -0.1, 1.1); // Ajusta los valores aquí
}


// Función para dibujar los ejes
void drawAxesWithLabels() {
    glBegin(GL_LINES);

    // Eje X
    glColor3f(0.0f, 0.0f, 0.0f);  // Negro
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(10.5f, 0.0f);

    // Eje Y
    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.0f, 1.1f);

    glEnd();

    // Etiquetas del eje X
    for (int i = 0; i <= 10; ++i) {
        std::string label = std::to_string(i);
        drawText(label.c_str(), i, -0.05f);  // Colocar ligeramente debajo del eje X
    }

    // Etiquetas del eje Y
    for (int i = 0; i <= 10; ++i) {
        float yLabel = i / 10.0f;
        std::string label = std::to_string(yLabel).substr(0, 4);  // Máximo 3 decimales
        drawText(label.c_str(), -0.2f, yLabel);  // Colocar ligeramente a la izquierda del eje Y
    }
}


// Función para graficar los puntos generados por la integración
void renderIntegrationPoints() {
    glColor3f(0.0f, 0.0f, 1.0f);  // Azul para los puntos
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    for (const auto& point : integrationPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

// Integrador numérico (GSL)
int func(double t, const double y[], double dydt[], void* params) {
    dydt[0] = std::sin(t) - y[0];
    return GSL_SUCCESS;
}


void runIntegration() {
    gsl_odeiv2_system sys = {func, nullptr, 1, nullptr};

    const gsl_odeiv2_step_type* T = gsl_odeiv2_step_rkf45;
    gsl_odeiv2_driver* d = gsl_odeiv2_driver_alloc_y_new(&sys, T, 0.1, 1e-6, 1e-6);

    double y[1] = {1.0};  // y(0) = 1
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

int main() {
    // Ejecutar la integración antes de inicializar la ventana
    runIntegration();

    // Inicializar GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Grafico de Integracion", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    // Inicializar GLUT
    int argc = 1;
    char* argv[1] = {const_cast<char*>("dummy")};
    glutInit(&argc, argv);

    // Configurar fondo blanco
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        setupViewport(window);  // Configurar la vista
        drawAxesWithLabels();             // Dibujar los ejes
        renderIntegrationPoints();  // Dibujar los puntos de integración

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

