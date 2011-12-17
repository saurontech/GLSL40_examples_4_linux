
GLM_INCLUDE_PATH = "C:/OpenGL/include"
GLEW_INCLUDE_PATH = "C:/OpenGL/include"
GLEW_LIB_PATH = "C:/OpenGL/lib"

QT       += opengl
CONFIG   += console

TARGET = chapter09

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
    vbocube.cpp \
    scenewave.cpp \
    sceneparticles.cpp \
    sceneparticlesfeedback.cpp \
    sceneparticlesinstanced.cpp \
    scenefire.cpp \
    scenesmoke.cpp \
    animtimer.cpp

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
    scenewave.h \
    sceneparticles.h \
    sceneparticlesfeedback.h \
    sceneparticlesinstanced.h \
    scenefire.h \
    scenesmoke.h \
    animtimer.h
