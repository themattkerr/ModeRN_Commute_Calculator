#-------------------------------------------------
#
# Project created by QtCreator 2017-12-28T20:57:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModeRN_Commute_Calculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        commute.cpp \
    changedefaultsdialog.cpp \
    ../General_Library/mattcalculations.cpp \
    aboutdialog.cpp

HEADERS  += commute.h \
    changedefaultsdialog.h \
    ../General_Library/mattcalculations.h \
    aboutdialog.h

FORMS    += commute.ui \
    changedefaultsdialog.ui \
    aboutdialog.ui

DISTFILES += \
    CarsSmall.ico \
    res.rc \
    install.nsi

RC_FILE = res.rc

#QMAKE_POST_LINK += windeployqt \"$$system_path($${OUT_PWD}/release/ModeRN_Commute_Calculator.exe)\" --dir \"$$system_path($${_PRO_FILE_PWD_}/Deploy)\"

#QMAKE_POST_LINK += && $$QMAKE_COPY \"$$system_path($${OUT_PWD}/release/ModeRN_Commute_Calculator.exe)\" \"$$system_path($${_PRO_FILE_PWD_}/Deploy/)\"
