#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T20:28:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TwentyFourPointsAlarmClockProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    calnode.cpp \
    originalnumber.cpp \
    calculatingclass.cpp \
    calculateexpressionalgorithm.cpp \
    calculateexpressionbyconvertingtosuffix.cpp

HEADERS  += mainwidget.h \
    calnode.h \
    dbconnection.h \
    originalnumber.h \
    calculatingclass.h \
    calculateexpressionalgorithm.h \
    calculateexpressionbyconvertingtosuffix.h

FORMS    += mainwidget.ui
