#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "scene.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class SceneBasic : public Scene
{
private:
    int width, height;
    GLuint vboHandles[2];
    GLuint vaoHandle;

    void linkMe(GLint vertShader, GLint fragShader);

public:
    SceneBasic();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_H
