
GLM_INCLUDE_PATH = "C:/include"
GLEW_INCLUDE_PATH = "C:/include"
GLEW_LIB_PATH = "C:/lib"

QT       += opengl
CONFIG   += console

TARGET = chapter01

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
    scenediffuse.cpp \
    drawable.cpp \
    vbotorus.cpp \
    vbomesh.cpp \
    sceneads.cpp \
    scenetwoside.cpp \
    vboteapot.cpp \
    sceneflat.cpp \
    scenesubroutine.cpp \
    scenediscard.cpp

HEADERS += \
    mainview.h \
    glutils.h \
    scene.h \
    glslprogram.h \
    scenediffuse.h \
    drawable.h \
    vbotorus.h \
    vbomesh.h \
    defines.h \
    sceneads.h \
    scenetwoside.h \
    vboteapot.h \
    teapotdata.h \
    sceneflat.h \
    scenesubroutine.h \
    scenediscard.h
