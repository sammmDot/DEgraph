QT += core gui widgets opengl openglwidgets

CONFIG += c++11

SOURCES += \
    grafico.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    grafico.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += imagenes.qrc


QRC

# Bibliotecas
INCLUDEPATH += /home/xime/Qt/6.7.3/gcc_64
LIBS += -L/usr/lib/x86_64-linux-gnu -lGL -lGLU


