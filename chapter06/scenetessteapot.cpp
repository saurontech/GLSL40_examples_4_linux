#include "scenetessteapot.h"

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

SceneTessTeapot::SceneTessTeapot()
{
    width = 800;
    height = 600;
}

void SceneTessTeapot::initScene()
{

    compileAndLinkShader();

    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glEnable(GL_DEPTH_TEST);

   // angle = PI / 2.0;

    angle = PI / 3.0;
    teapot = new VBOTeapotPatch();

    ///////////// Uniforms ////////////////////
    prog.setUniform("TessLevel", 4);
    prog.setUniform("LineWidth", 0.8f);
    prog.setUniform("LineColor", vec4(0.05f,0.0f,0.05f,1.0f));
    prog.setUniform("LightPosition", vec4(0.0f,0.0f,0.0f,1.0f));
    prog.setUniform("LightIntensity", vec3(1.0f,1.0f,1.0f));
    prog.setUniform("Kd", vec3(0.9f, 0.9f, 1.0f));
    /////////////////////////////////////////////

    glPatchParameteri(GL_PATCH_VERTICES, 16);
}


void SceneTessTeapot::update( float t )
{
    angle += 0.005f;
    if( angle > TWOPI) angle -= TWOPI;
}

void SceneTessTeapot::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3 cameraPos(4.25f * cos(angle),3.0f,4.25f * sin(angle));
    view = glm::lookAt(cameraPos,
                       vec3(0.0f,0.0f,0.0f),
                       vec3(0.0f,1.0f,0.0f));

    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f,-1.5f,0.0f));
    model = glm::rotate(model,-90.0f, vec3(1.0f,0.0f,0.0f));
    setMatrices();
    teapot->render();
    glFinish();
}

void SceneTessTeapot::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
    prog.setUniform("ViewportMatrix", viewport);
}

void SceneTessTeapot::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;

    float w2 = w / 2.0f;
    float h2 = h / 2.0f;
    viewport = mat4( vec4(w2,0.0f,0.0f,0.0f),
                     vec4(0.0f,h2,0.0f,0.0f),
                     vec4(0.0f,0.0f,1.0f,0.0f),
                     vec4(w2+0, h2+0, 0.0f, 1.0f));
    projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneTessTeapot::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/tessteapot.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/tessteapot.gs",GLSLShader::GEOMETRY) )
    {
        printf("Geometry shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/tessteapot.fs",GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/tessteapot.tes",GLSLShader::TESS_EVALUATION))
    {
        printf("Tess evaluation shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/tessteapot.tcs",GLSLShader::TESS_CONTROL))
    {
        printf("Tess control shader failed to compile!\n%s",
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
