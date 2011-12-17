#ifndef SCENENORMALMAP_H
#define SCENENORMALMAP_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbocube.h"
#include "vbomesh.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneNormalMap : public Scene
{
private:
    GLSLProgram prog;

    int width, height;
    VBOPlane *plane;
    VBOCube *cube;
    VBOMesh *ogre;

    mat4 model;
    mat4 view;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();

public:
    SceneNormalMap();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENENORMALMAP_H
