#-------------------------------------------------
#
# Project created by QtCreator 2019-07-06T09:09:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kechengsheji
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        course_function.cpp \
        course_score.cpp \
        main.cpp \
        operate_score.cpp \
        outputscore.cpp \
        student_function.cpp \
        system.cpp

HEADERS += \
        course.h \
        course_function.h \
        course_score.h \
        extravector.h \
        operate_score.h \
        outputscore.h \
        score.h \
        student.h \
        student_function.h \
        system.h \
        teacher.h

FORMS += \
        course_function.ui \
        course_score.ui \
        operate_score.ui \
        outputscore.ui \
        student_function.ui \
        system.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/hehehe.qrc
