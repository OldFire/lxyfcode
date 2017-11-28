QT += core
QT -= gui

CONFIG += c++11

TARGET = opencv_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=


INCLUDEPATH+=C:\opencv\include\opencv\
                    C:\opencv\include\opencv2\
                    C:\opencv\include

LIBS+=C:\opencv\lib\libopencv_calib3d243.dll.a\
        C:\opencv\lib\libopencv_contrib243.dll.a\
        C:\opencv\lib\libopencv_core243.dll.a\
        C:\opencv\lib\libopencv_features2d243.dll.a\
        C:\opencv\lib\libopencv_flann243.dll.a\
        C:\opencv\lib\libopencv_gpu243.dll.a\
        C:\opencv\lib\libopencv_highgui243.dll.a\
        C:\opencv\lib\libopencv_imgproc243.dll.a\
        C:\opencv\lib\libopencv_legacy243.dll.a\
        C:\opencv\lib\libopencv_ml243.dll.a\
        C:\opencv\lib\libopencv_objdetect243.dll.a\
        C:\opencv\lib\libopencv_video243.dll.a

RESOURCES +=


