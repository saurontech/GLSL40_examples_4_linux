#include "scenesilhouette.h"

#include <cstdio>
#include <cstdlib>
using std::rand;
using std::srand;
#include <ctime>
using std::time;

#include <QImage>
#include <QGLWidget>

#include "glutils.h"
#include "defines.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

SceneSilhouette::SceneSilhouette()
{
    width = 800;
    height = 600;
}

void SceneSilhouette::initScene()
{
    compileAndLinkShader();

    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glEnable(GL_DEPTH_TEST);

    ogre = new VBOMeshAdj("mesh/bs_ears.obj");

    angle = PI / 2.0;    

    ///////////// Uniforms ////////////////////
    prog.setUniform("EdgeWidth", 0.015f);
    prog.setUniform("PctExtend", 0.25f);
    prog.setUniform("LineColor", vec4(0.05f,0.0f,0.05f,1.0f));
    prog.setUniform("Material.Kd", 0.7f, 0.5f, 0.2f);
    prog.setUniform("Light.Position", 0.0f,0.0f,0.0f);
    prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Light.Intensity", 1.0f, 1.0f, 1.0f);
    /////////////////////////////////////////////

}


void SceneSilhouette::update( float t )
{
    angle += 0.001f;
    if( angle > TWOPI) angle -= TWOPI;
}

void SceneSilhouette::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3 cameraPos(1.5f * cos(angle),0.0f,1.5f * sin(angle));
    view = glm::lookAt(cameraPos,
                       vec3(0.0f,-0.2f,0.0f),
                       vec3(0.0f,1.0f,0.0f));

    model = mat4(1.0f);
    setMatrices();
    ogre->render();

    glFinish();
}

void SceneSilhouette::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneSilhouette::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneSilhouette::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/silhouette.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/silhouette.gs",GLSLShader::GEOMETRY) )
    {
        printf("Geometry shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/silhouette.fs",GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.link() )
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }

    prog.use();
}
