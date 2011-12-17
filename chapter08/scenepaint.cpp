#include "scenepaint.h"

#include <cstdio>

#include <QImage>
#include <QGLWidget>

#include "glutils.h"
#include "defines.h"
#include "noisetex.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include<iostream>

ScenePaint::ScenePaint()
{
    width = 800;
    height = 600;
}

void ScenePaint::initScene()
{
    compileAndLinkShader();

    glClearColor(0.1f,0.1f,0.1f,1.0f);

    glEnable(GL_DEPTH_TEST);

    prog.setUniform("NoiseTex", 0);

    GLuint noiseTex = NoiseTex::generate2DTex(true, 32.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, noiseTex);

    teapot = new VBOTeapot(14, mat4(1.0f));

    prog.setUniform("Light.Intensity", vec3(1.0f,1.0f,1.0f));
    lightPos = vec4(0.0f,0.0f,0.0f,1.0f);
    prog.setUniform("LowThreshold", 0.35f);
    prog.setUniform("HighThreshold", 0.65f);
}

void ScenePaint::update( float t ) { }

void ScenePaint::render()
{
    prog.setUniform("Light.Position", lightPos);

    vec3 cameraPos = 0.85f * vec3(0.0f,5.0f,6.0f);
    view = glm::lookAt(cameraPos, vec3(0.0f,0.0f,-3.0f), vec3(0.0f,1.0f,0.0f));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScene();
    glFinish();
}

void ScenePaint::drawScene()
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

void ScenePaint::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void ScenePaint::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(55.0f, (float)width/height, 0.3f, 100.0f);
}

void ScenePaint::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/paint.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/paint.fs",GLSLShader::FRAGMENT))
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
