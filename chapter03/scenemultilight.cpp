#include "scenemultilight.h"

#include <cstdio>
#include <cstdlib>

#include "glutils.h"
#include "defines.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

SceneMultiLight::SceneMultiLight()
{
}

void SceneMultiLight::initScene()
{
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);

    plane = new VBOPlane(10.0f, 10.0f, 100, 100);
    mesh = new VBOMesh("media/pig_triangulated.obj",true);

   // model *= glm::rotate(35.0f, vec3(0.0f,1.0f,0.0f));
    view = glm::lookAt(vec3(0.5f,0.75f,0.75f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = mat4(1.0f);

    char name[20];
    float x, z;
    for( int i = 0; i < 5; i++ ) {
        snprintf(name, 20, "lights[%d].Position", i);
        x = 2.0 * cos((TWOPI / 5) * i);
        z = 2.0 * sin((TWOPI / 5) * i);
        prog.setUniform(name, view * vec4(x, 1.2f, z + 1.0f, 1.0f) );
    }

    prog.setUniform("lights[0].Intensity", vec3(0.0f,0.8f,0.8f) );
    prog.setUniform("lights[1].Intensity", vec3(0.0f,0.0f,0.8f) );
    prog.setUniform("lights[2].Intensity", vec3(0.8f,0.0f,0.0f) );
    prog.setUniform("lights[3].Intensity", vec3(0.0f,0.8f,0.0f) );
    prog.setUniform("lights[4].Intensity", vec3(0.8f,0.8f,0.8f) );
}

void SceneMultiLight::update( float t )
{

}

void SceneMultiLight::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog.setUniform("Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Shininess", 180.0f);

    model = mat4(1.0f);
    model *= glm::rotate(90.0f, vec3(0.0f,1.0f,0.0f));
    setMatrices();
    mesh->render();

    prog.setUniform("Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Shininess", 180.0f);

    model = mat4(1.0f);
    model *= glm::translate(vec3(0.0f,-0.45f,0.0f));
    setMatrices();
    plane->render();
}

void SceneMultiLight::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneMultiLight::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(70.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneMultiLight::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/multilight.vert",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/multilight.frag",GLSLShader::FRAGMENT))
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
