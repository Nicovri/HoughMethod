#-------------------------------------------------
#
# Project created by QtCreator 2021-05-19T11:05:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HoughMethod
TEMPLATE = app


SOURCES += main.cpp\
    image.cpp \
    mainwindow.cpp \
    houghcircleform.cpp \
    grayscaleform.cpp \
    filter3form.cpp \
    houghlineform.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += C:\\OpenCV2.4\\include
LIBS += -LC:\\OpenCV2.4\\build-qt\\lib \
    -lopencv_calib3d249d \
    -lopencv_contrib249d \
    -lopencv_core249d \
    -lopencv_features2d249d \
    -lopencv_flann249d \
    -lopencv_gpu249d \
    -lopencv_highgui249d \
    -lopencv_imgproc249d \
    -lopencv_legacy249d \
    -lopencv_ml249d \
    -lopencv_nonfree249d \
    -lopencv_objdetect249d \
    -lopencv_ocl249d \
    -lopencv_photo249d \
    -lopencv_stitching249d \
    -lopencv_superres249d \
    -lopencv_ts249d \
    -lopencv_video249d \
    -lopencv_videostab249d

HEADERS  += mainwindow.h \
    image.h \
    houghcircleform.h \
    grayscaleform.h \
    filter3form.h \
    houghlineform.h \
    image.h

FORMS    += mainwindow.ui \
    houghcircleform.ui \
    grayscaleform.ui \
    filter3form.ui \
    houghlineform.ui

QMAKE_CXXFLAGS += -std=gnu++14
