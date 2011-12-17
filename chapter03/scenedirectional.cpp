#include "scenedirectional.h"

#include <cstdio>
#include <cstdlib>

#include "glutils.h"
#include "defines.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

SceneDirectional::SceneDirectional()
{
}

void SceneDirectional::initScene()
{
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);

    plane = new VBOPlane(10.0f, 10.0f, 100, 100);
    torus = new VBOTorus(0.7f, 0.3f, 50, 50);

    view = glm::lookAt(vec3(1.0f,1.0f,1.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = mat4(1.0f);

 //  prog.setUniform("LightPosition", view * vec4(3.0f, 0.0f, 0.0f, 1.0f) );
    prog.setUniform("LightPosition", view * vec4(1.0f, 0.0f, 0.0f, 0.0f) );
    prog.setUniform("LightIntensity", vec3(0.8f,0.8f,0.8f) );
}

void SceneDirectional::update( float t )
{

}

void SceneDirectional::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog.setUniform("Kd", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Shininess", 180.0f);

    model = mat4(1.0f);
    model *= glm::rotate(90.0f, vec3(0.0f,1.0f,0.0f));
    setMatrices();
    torus->render();

    prog.setUniform("Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Shininess", 180.0f);

    model = mat4(1.0f);
    model *= glm::translate(vec3(0.0f,-0.45f,0.0f));
    setMatrices();
    //plane->render();
}

void SceneDirectional::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneDirectional::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(70.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneDirectional::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/directional.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/directional.fs",GLSLShader::FRAGMENT))
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
