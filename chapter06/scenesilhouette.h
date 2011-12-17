#ifndef SCENESILHOUETTE_H
#define SCENESILHOUETTE_H

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

class SceneSilhouette : public Scene
{
private:
    GLSLProgram prog;

    int width, height;

    VBOMeshAdj *ogre;

    mat4 model;
    mat4 view, viewport;
    mat4 projection;
    float angle;

    void setMatrices();
    void compileAndLinkShader();
    void setupFBO();

public:
    SceneSilhouette();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENESILHOUETTE_H
