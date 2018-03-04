#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T16:15:07
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PVZ
TEMPLATE = app


SOURCES += main.cpp\
        startwindow.cpp \
    gamewindow.cpp \
    zoobie.cpp \
    pea.cpp \
    wallnut.cpp \
    shovel.cpp \
    sunflower.cpp \
    sunshine.cpp \
    bucketzoobie.cpp \
    plant.cpp \
    globalvariable.cpp \
    bullet.cpp \
    polevaultingzoobie.cpp \
    lawncleaner.cpp

HEADERS  += startwindow.h \
    gamewindow.h \
    pea.h \
    wallnut.h \
    shovel.h \
    sunflower.h \
    zoobie.h \
    sunshine.h \
    bucketzoobie.h \
    plant.h \
    globalvariable.h \
    bullet.h \
    polevaultingzoobie.h \
    lawncleaner.h

FORMS    += startwindow.ui \
    gamewindow.ui

RESOURCES += \
    myresource.qrc
