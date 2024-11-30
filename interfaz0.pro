QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Incluye las rutas y la biblioteca de muParser
INCLUDEPATH += /usr/include  # Ajusta esta ruta si la biblioteca está en otra ubicación
LIBS += -L/usr/lib -lmuparser  # Ajusta esta ruta si la biblioteca está en otra ubicación

# Incluye las rutas y bibliotecas de GSL
INCLUDEPATH += /usr/include/gsl  # Ruta para los encabezados de GSL
LIBS += -lgsl -lgslcblas          # Enlaza las bibliotecas GSL y gslcblas

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
