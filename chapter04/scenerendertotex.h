#ifndef SCENERENDERTOTEX_H
#define SCENERENDERTOTEX_H

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

class SceneRenderToTex : public Scene
{
private:
    GLSLProgram prog;

    GLuint fboHandle;
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
    void setupFBO();
    void renderToTexture();
    void renderScene();

public:
    SceneRenderToTex();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENERENDERTOTEX_H
