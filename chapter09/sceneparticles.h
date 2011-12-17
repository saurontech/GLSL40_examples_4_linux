#ifndef SCENEPARTICLES_H
#define SCENEPARTICLES_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbocube.h"
#include "vbotorus.h"
#include "vboteapot.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
using glm::mat4;

class SceneParticles : public Scene
{
private:
    GLSLProgram prog;

    int width, height;
    GLuint initVel, startTime, particles;
    GLuint nParticles;

    VBOPlane *plane;

    mat4 model;
    mat4 view;
    mat4 projection;
    float angle;
    float time;

    void setMatrices();
    void compileAndLinkShader();
    void initBuffers();
    float randFloat();

public:
    SceneParticles();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEPARTICLES_H
