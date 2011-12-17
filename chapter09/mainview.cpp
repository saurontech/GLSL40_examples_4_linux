#include "mainview.h"
#include "scenesmoke.h"

#include "glutils.h"

#include <iostream>
using std::cout;
using std::endl;
#include <cstdio>

MainView::MainView(const QGLFormat & format, QWidget *parent) : QGLWidget(format, parent)
{
    // This tells the widget to accept keyboard focus when the widget is clicked.
    this->setFocusPolicy(Qt::ClickFocus);

    timer = new QTimer(this);
    timer->setInterval(20);
    connect( timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );

    this->setMinimumSize(800,600);

    lastStop = 0.0;
    time = 0.0;
    startTime = 0.0;
}

void MainView::initializeGL() {

    //////////////// PLUG IN SCENE HERE /////////////////
    scene = new SceneSmoke();
    ////////////////////////////////////////////////////

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if( GLEW_OK != err )
    {
        cout <<"Error initializing GLEW: " << glewGetErrorString(err) << endl;
    }
    GLUtils::checkForOpenGLError(__FILE__,__LINE__);

    QGLFormat format = this->format();
    printf("QGLFormat reports profile: ");
    if( format.profile() == QGLFormat::CompatibilityProfile )
        printf("compatability.\n");
    else if( format.profile() == QGLFormat::CoreProfile )
        printf("core.\n");
    else
        printf("none.\n");

    GLUtils::dumpGLInfo();

    glClearColor(0.5f,0.5f,0.5f,1.0f);

    scene->initScene();
}

void MainView::paintGL() {
    GLUtils::checkForOpenGLError(__FILE__,__LINE__);
    scene->render();
}

void MainView::resizeGL(int w, int h ) {
    scene->resize(w,h);
}

void MainView::takeScreenShot() {
    QImage img = this->grabFrameBuffer();
    img.save("screen.png", "PNG");
}

void MainView::toggleAnimation() {
    if( timer->isActive() ) {
        animTimer.stop();
        timer->stop();
    } else {
        animTimer.start();
        timer->start();
    }
}

void MainView::timerUpdate() {
    scene->update(animTimer.curTime());
    updateGL();
}

