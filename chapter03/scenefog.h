#ifndef SCENEFOG_H
#define SCENEFOG_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vboteapot.h"
#include "vbotorus.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneFog : public Scene
{
private:
    GLSLProgram prog;

    int width, height;
    VBOPlane *plane;
    VBOTeapot *teapot;
    VBOTorus *torus;

    mat4 model;
    mat4 view;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();

public:
    SceneFog();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEFog_H
