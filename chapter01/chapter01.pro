
GLM_INCLUDE_PATH = "/user/include/"
GLEW_INCLUDE_PATH = "/usr/include/"
GLEW_LIB_PATH = "/usr/lib/"

QT       += opengl
CONFIG   += console

TARGET = chapter01

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
    scenebasic.cpp \
    scenebasic_layout.cpp \
    scenebasic_uniform.cpp \
    scenebasic_uniformblock.cpp \
    glslprogram.cpp

HEADERS += \
    mainview.h \
    glutils.h \
    scene.h \
    scenebasic.h \
    scenebasic_layout.h \
    scenebasic_uniform.h \
    scenebasic_uniformblock.h \
    glslprogram.h
