#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>
#include <cmath>
#include <vector>
#include <iostream>

// Estructura para almacenar puntos 3D
struct Point3D {
    float x, y, z;
};

std::vector<Point3D> integrationPoints;  // Puntos generados por la integración

// Parámetros del sistema de Lorenz
const double sigma = 10.0;
const double rho = 28.0;
const double beta = 8.0 / 3.0;

// Función para definir el sistema de Lorenz
int lorenzSystem(double t, const double y[], double dydt[], void* params) {
    dydt[0] = sigma * (y[1] - y[0]);
    dydt[1] = y[0] * (rho - y[2]) - y[1];
    dydt[2] = y[0] * y[1] - beta * y[2];
    return GSL_SUCCESS;
}

// Integrador numérico (GSL)
void runIntegration() {
    gsl_odeiv2_system sys = {lorenzSystem, nullptr, 3, nullptr};

    const gsl_odeiv2_step_type* T = gsl_odeiv2_step_rkf45;
    gsl_odeiv2_driver* d = gsl_odeiv2_driver_alloc_y_new(&sys, T, 0.01, 1e-6, 1e-6);

    double y[3] = {1.0, 1.0, 1.0};  // Condiciones iniciales
    double t = 0.0;
    double t1 = 50.0;
    int num_points = 100000;
    double dt = t1 / (num_points - 1);

    for (int i = 0; i < num_points; i++) {
        double t_actual = i * dt;
        gsl_odeiv2_driver_apply(d, &t, t_actual, y);
        integrationPoints.push_back({static_cast<float>(y[0]), static_cast<float>(y[1]), static_cast<float>(y[2])});
    }

    gsl_odeiv2_driver_free(d);
}

// Configuración de la cámara para 3D
void setupViewport3D(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, width / (float)height, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(50.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

// Dibujar los puntos generados por la integración
void renderIntegrationPoints3D() {
    glColor3f(0.0f, 0.0f, 1.0f);  // Azul para los puntos
    glBegin(GL_LINE_STRIP);       // Usar líneas conectadas para un gráfico fluido
    for (const auto& point : integrationPoints) {
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
}

// Dibujar ejes 3D
void renderAxes() {
    glColor3f(0.0f, 0.0f, 0.0f);  // Negro para los ejes
    glBegin(GL_LINES);
    // Eje X
    glVertex3f(-300.0f, 0.0f, 0.0f);
    glVertex3f(300.0f, 0.0f, 0.0f);

    // Eje Y
    glVertex3f(0.0f, -300.0f, 0.0f);
    glVertex3f(0.0f, 300.0f, 0.0f);

    // Eje Z
    glVertex3f(0.0f, 0.0f, -300.0f);
    glVertex3f(0.0f, 0.0f, 300.0f);
    glEnd();
}

// Configurar el fondo blanco
void setupBackground() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Blanco
}

int main() {
    // Ejecutar la integración antes de inicializar la ventana
    runIntegration();

    // Inicializar GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mariposa de Lorenz", NULL, NULL);
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

    setupBackground();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);  // Habilitar profundidad para 3D

        setupViewport3D(window);       // Configurar la vista 3D
        renderAxes();                  // Dibujar los ejes
        renderIntegrationPoints3D();  // Dibujar los puntos de integración

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

