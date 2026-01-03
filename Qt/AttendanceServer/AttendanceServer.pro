QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#添加opencv，seetaface头文件
INCLUDEPATH += /home/abcooxj/opencv/Face_opencv4_up/opencv-4.5.2/install/include
INCLUDEPATH += /home/abcooxj/opencv/Face_opencv4_up/opencv-4.5.2/install/include/opencv4/opencv2
INCLUDEPATH += /home/abcooxj/opencv/Face_opencv4_up/opencv-4.5.2/install/include/opencv4
INCLUDEPATH += /home/abcooxj/opencv/Face_opencv4_up/opencv-4.5.2/install/include/seeta
#添加opencv，seetace的库
#-L/usr/lib/x86_64-linux-gnu
LIBS+=-L/home/abcooxj/opencv/Face_opencv4_up/opencv-4.5.2/install/lib -lopencv_world -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer -lSeetaFaceTracker -lSeetaNet -lSeetaQualityAssessor


SOURCES += \
    main.cpp \
    attendancewin.cpp \
    qfaceobject.cpp \
    registerwin.cpp \
    selectwin.cpp

HEADERS += \
    attendancewin.h \
    qfaceobject.h \
    registerwin.h \
    selectwin.h

FORMS += \
    attendancewin.ui \
    registerwin.ui \
    selectwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
