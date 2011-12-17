#ifndef SCENESHADEWIRE_H
#define SCENESHADEWIRE_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbocube.h"
#include "vbotorus.h"
#include "vboteapot.h"
#include "vbomesh.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneShadeWire : public Scene
{
private:
    GLSLProgram prog;

    int width, height;

    VBOMesh *ogre;

    mat4 model;
    mat4 view, viewport;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();
    void setupFBO();

public:
    SceneShadeWire();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENESHADEWIRE_H
