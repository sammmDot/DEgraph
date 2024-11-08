#include <stdio.h>
#include <iostream>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>
#include <cmath>

using namespace std;

// Definición de la función que representa la EDO
int func(double t, const double y[], double dydt[], void *params)
{
    dydt[0] = -2 * y[0]; // dy/dt = -2y
    return GSL_SUCCESS;
}

// Definición de la estructura para el sistema de EDO
struct ode_params
{
    double some_param; // Puedes agregar otros parámetros si es necesario
};

int main()
{
    // Inicialización de la biblioteca GSL
    gsl_set_error_handler_off();

    // Inicialización de los parámetros de la EDO
    ode_params params;

    // Definición del sistema de EDO
    gsl_odeiv2_system sys = {func, nullptr, 1, &params};

    // Creación del stepper
    const gsl_odeiv2_step_type *T = gsl_odeiv2_step_rkf45; // Elegimos un método Runge-Kutta-Fehlberg
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, T, 0.1, 1e-6, 1e-6);

    // Condición inicial
    double y[1] = {1.0}; // y(0) = 1
    double t = 0.0;      // Tiempo inicial
    double t1 = 5.0;     // Tiempo final

    // Definir número de puntos y el incremento de tiempo
    int num_points = 100;
    double dt = t1 / (num_points - 1);

    // Integración de la EDO en 100 puntos
    for (int i = 0; i < num_points; i++)
    {
        double t_actual = i * dt;                    // Tiempo en el cual queremos evaluar
        gsl_odeiv2_driver_apply(d, &t, t_actual, y); // Integrar hasta t_actual
        cout << "t = " << t << ", y = " << y[0] << ", analítica = " << exp(-2 * t) << endl;
    }

    // Liberación de memoria
    gsl_odeiv2_driver_free(d);

    return 0;
}
