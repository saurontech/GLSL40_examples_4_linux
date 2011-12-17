#ifndef SCENETESSTEAPOT_H
#define SCENETESSTEAPOT_H

#include "scene.h"
#include "glslprogram.h"
#include "vboteapotpatch.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneTessTeapot : public Scene
{
private:
    GLSLProgram prog;

    GLuint vaoHandle;
    int width, height;

    VBOTeapotPatch *teapot;

    mat4 model;
    mat4 view, viewport;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();

public:
    SceneTessTeapot();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENETESSTEAPOT_H
