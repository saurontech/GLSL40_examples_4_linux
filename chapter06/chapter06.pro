
GLM_INCLUDE_PATH = "C:/include"
GLEW_INCLUDE_PATH = "C:/include"
GLEW_LIB_PATH = "C:/lib"

QT       += opengl
CONFIG   += console

TARGET = chapter06

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
    vbomeshadj.cpp \
    vboteapot.cpp \
    vboplane.cpp \
    vbocube.cpp \
    vboteapotpatch.cpp \
    scenepointsprite.cpp \
    sceneshadewire.cpp \
    scenesilhouette.cpp \
    scenequadtess.cpp \
    scenebezcurve.cpp \
    scenetessteapot.cpp \
    scenetessteapotdepth.cpp


HEADERS += \
    mainview.h \
    glutils.h \
    scene.h \
    glslprogram.h \
    drawable.h \
    vbotorus.h \
    vbomesh.h \
    vbomeshadj.h \
    defines.h \
    vboteapot.h \
    teapotdata.h \
    vboplane.h \
    vbocube.h \
    vboteapotpatch.h \
    scenepointsprite.h \
    sceneshadewire.h \
    scenesilhouette.h \
    scenequadtess.h \
    scenebezcurve.h \
    scenetessteapot.h \
    scenetessteapotdepth.h
