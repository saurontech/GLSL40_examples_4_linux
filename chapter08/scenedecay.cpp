#include "scenedecay.h"

#include <cstdio>

#include <QImage>
#include <QGLWidget>

#include "glutils.h"
#include "defines.h"
#include "noisetex.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/matrix_projection.hpp>

#include<iostream>

SceneDecay::SceneDecay()
{
    width = 800;
    height = 600;
}

void SceneDecay::initScene()
{
    compileAndLinkShader();

    glClearColor(0.1f,0.1f,0.1f,1.0f);

    glEnable(GL_DEPTH_TEST);

    prog.setUniform("NoiseTex", 0);

    GLuint noiseTex = NoiseTex::generate2DTex(true);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, noiseTex);

    teapot = new VBOTeapot(14, mat4(1.0f));

    prog.setUniform("Light.Intensity", vec3(1.0f,1.0f,1.0f));
    lightPos = vec4(0.0f,0.0f,0.0f,1.0f);
    prog.setUniform("LowThreshold", 0.35f);
    prog.setUniform("HighThreshold", 0.65f);
}

void SceneDecay::update( float t ) { }

void SceneDecay::render()
{
    prog.setUniform("Light.Position", lightPos);

    vec3 cameraPos = 0.85f * vec3(0.0f,5.0f,6.0f);
    view = glm::lookAt(cameraPos, vec3(0.0f,0.0f,-3.0f), vec3(0.0f,1.0f,0.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScene();
    glFinish();
}

void SceneDecay::drawScene()
{    
    model = mat4(1.0f);
    model = glm::rotate(model, -15.0f, vec3(0.0f,1.0f,0.0f));
    model = glm::rotate(model, -90.0f, vec3(1.0f,0.0f,0.0f));
    setMatrices();

    prog.setUniform("Material.Kd", 0.7f, 0.5f, 0.3f);
    prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Shininess", 100.0f);

    teapot->render();
}

void SceneDecay::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneDecay::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(55.0f, (float)width/height, 0.3f, 100.0f);
}

void SceneDecay::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/decay.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/decay.fs",GLSLShader::FRAGMENT))
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
