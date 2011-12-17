#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "mainview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // The main window
    QWidget win;

    // The GL view
    QGLFormat format;
    format.setVersion(4,0);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(true);
    format.setSamples(16);
    MainView *glView = new MainView(format);

    QVBoxLayout *mainLayout = new QVBoxLayout(&win);
    mainLayout->addWidget(glView);

    QWidget *cPanel = new QWidget(&win);
    QHBoxLayout *cPanelLayout = new QHBoxLayout();
    cPanel->setLayout(cPanelLayout);

    QPushButton *sShotButton = new QPushButton("Screen Shot");
    cPanelLayout->addWidget(sShotButton);
    QObject::connect( sShotButton, SIGNAL(clicked()), glView, SLOT(takeScreenShot()) );

    QPushButton *animButton = new QPushButton("Start/Stop Animation");
    cPanelLayout->addWidget(animButton);
    QObject::connect(animButton, SIGNAL(clicked()), glView, SLOT(toggleAnimation()) );

    mainLayout->addWidget(cPanel);

    win.setLayout(mainLayout);
    win.setWindowTitle("Chapter 1 Examples");
    win.show();

    return app.exec();
}

