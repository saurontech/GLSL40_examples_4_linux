
GLM_INCLUDE_PATH = "C:/OpenGL/include"
GLEW_INCLUDE_PATH = "C:/OpenGL/include"
GLEW_LIB_PATH = "C:/OpenGL/lib"

QT       += opengl
CONFIG   += console

TARGET = chapter04

win32 {
    CONFIG   -= app_bundle
    LIBS += -L$$GLEW_LIB_PATH -lglew32
}
unix{
	LIBS += -lGLEW -lGLU
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
    scenetexture.cpp \
    scenemultitex.cpp \
    scenenormalmap.cpp \
    scenereflectcube.cpp \
    skybox.cpp \
    scenerefractcube.cpp \
    sceneprojtex.cpp \
    scenealphatest.cpp \
    scenerendertotex.cpp


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
    scenetexture.h \
    scenemultitex.h \
    scenenormalmap.h \
    scenereflectcube.h \
    skybox.h \
    scenerefractcube.h \
    sceneprojtex.h \
    scenealphatest.h \
    scenerendertotex.h
