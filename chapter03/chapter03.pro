
GLM_INCLUDE_PATH = "C:/include"
GLEW_INCLUDE_PATH = "C:/include"
GLEW_LIB_PATH = "C:/lib"

QT       += opengl
CONFIG   += console

TARGET = chapter03

win32 {
    CONFIG   -= app_bundle
    LIBS += -L$$GLEW_LIB_PATH -lglew32
}

unix{
	LIBS += -lGLEW
}

TEMPLATE = app

INCLUDEPATH += $$GLM_INCLUDE_PATH $$GLEW_INCLUDE_PATH

SOURCES += main.cpp \
    mainview.cpp \
    glutils.cpp \
    glslprogram.cpp \
    drawable.cpp \
    vbotorus.cpp \
    vbomesh.cpp \
    vboteapot.cpp \
    vboplane.cpp \
    scenemultilight.cpp \
    scenedirectional.cpp \
    sceneperfragment.cpp \
    scenespot.cpp \
    scenetoon.cpp \
    scenefog.cpp

HEADERS += \
    mainview.h \
    glutils.h \
    scene.h \
    glslprogram.h \
    drawable.h \
    vbotorus.h \
    vbomesh.h \
    defines.h \
    vboteapot.h \
    teapotdata.h \
    vboplane.h \
    scenemultilight.h \
    scenedirectional.h \
    sceneperfragment.h \
    scenespot.h \
    scenetoon.h \
    scenefog.h
