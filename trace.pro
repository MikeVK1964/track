#-------------------------------------------------
#
# Project created by QtCreator 2021-07-26T10:23:04
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trace
TEMPLATE = app


SOURCES += main.cpp\
    baseiko.cpp \
    dlgimit.cpp \
    doctras.cpp \
    mkapp.cpp \
    mkimitthread.cpp \
    mknetserver.cpp \
    new_traceview.cpp \
    iko.cpp \
    proppointtr.cpp \
    rightform.cpp \
    mainwindowTrace.cpp \
    statmem.cpp \
    setcontrol.cpp \
    si_xh.cpp \
    maketras.cpp

HEADERS  += \
    DocTrace.h \
    baseiko.h \
    dlgimit.h \
    mkapp.h \
    mkimitthread.h \
    mknetserver.h \
    new_traceview.h \
    iko.h \
    proppointtr.h \
    rightform.h \
    mainwindowTrace.h \
    setcontrol.h \
    convcoor.h \
    si_xh.h \
    maketras.h

FORMS += \
    dlgimit.ui \
    proppointtr.ui \
    rightform.ui

RESOURCES += \
    trace.qrc
