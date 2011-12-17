#ifndef SCENEREFRACTCUBE_H
#define SCENEREFRACTCUBE_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbocube.h"
#include "vbomesh.h"
#include "vboteapot.h"
#include "vbotorus.h"
#include "skybox.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneRefractCube : public Scene
{
private:
    GLSLProgram prog;

    int width, height;
    VBOTeapot *teapot;
    VBOTorus *torus;
    VBOPlane *plane;
    SkyBox *sky;

    mat4 model;
    mat4 view;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();
    void loadCubeMap( const char * baseFileName );

public:
    SceneRefractCube();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEREFRACTCUBE_H
