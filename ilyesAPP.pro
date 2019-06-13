#-------------------------------------------------
#
# Project created by QtCreator 2017-12-04T16:15:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ilyesAPP
TEMPLATE = app



SOURCES += main.cpp\
        create.cpp \
    login.cpp \
    uploadimage.cpp \
    imageprocess.cpp

HEADERS  += create.h \
    login.h \
    uploadimage.h \
    imageprocess.h

FORMS    += create.ui \
    login.ui \
    uploadimage.ui

RESOURCES += \
    images/resources.qrc
