#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T10:21:32
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = AgatScanner
TEMPLATE = app

win32 {
        RC_FILE += file.rc
        OTHER_FILES += file.rc
}

SOURCES += main.cpp\
        mainwindow.cpp \
    sg_comport.cpp \
    agat.cpp \
    agatsetting.cpp \
    cgraphwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    sg_comport.h \
    agat.h \
    agatsetting.h \
    cgraphwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    cgraphwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    file.rc
