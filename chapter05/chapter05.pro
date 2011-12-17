
GLM_INCLUDE_PATH = "C:/include"
GLEW_INCLUDE_PATH = "C:/include"
GLEW_LIB_PATH = "C:/lib"

QT       += opengl
CONFIG   += console

TARGET = chapter05

win32 {
    CONFIG   -= app_bundle
    LIBS += -L$$GLEW_LIB_PATH -lglew32
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
    vbocube.cpp \
    sceneedge.cpp \
    sceneblur.cpp \
    scenebloom.cpp \
    scenegamma.cpp \
    scenemsaa.cpp \
    scenedeferred.cpp


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
    vbocube.h \
    sceneedge.h \
    sceneblur.h \
    scenebloom.h \
    scenegamma.h \
    scenemsaa.h \
    scenedeferred.h
