#ifndef SCENEMULTILIGHT_H
#define SCENEMULTILIGHT_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbomesh.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneMultiLight : public Scene
{
private:
    GLSLProgram prog;

    int width, height;
    VBOPlane *plane;
    VBOMesh * mesh;

    mat4 model;
    mat4 view;
    mat4 projection;

    void setMatrices();
    void compileAndLinkShader();

public:
    SceneMultiLight();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEMULTILIGHT_H
