#ifndef SCENEBEZCURVE_H
#define SCENEBEZCURVE_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbocube.h"
#include "vbotorus.h"
#include "vboteapot.h"
#include "vbomeshadj.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneBezCurve : public Scene
{
private:
    GLSLProgram prog;
    GLSLProgram solidProg;

    GLuint vaoHandle;
    int width, height;

    mat4 model;
    mat4 view, viewport;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();

public:
    SceneBezCurve();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBEZCURVE_H
