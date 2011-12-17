#ifndef SCENEALPHATEST_H
#define SCENEALPHATEST_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbocube.h"
#include "vboteapot.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneAlphaTest : public Scene
{
private:
    GLSLProgram prog;

    int width, height;
    VBOPlane *plane;
    VBOCube *cube;
    VBOTeapot *teapot;

    mat4 model;
    mat4 view;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();

public:
    SceneAlphaTest();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEALPHATEST_H
