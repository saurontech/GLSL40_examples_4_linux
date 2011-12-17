#include "sceneflat.h"

#include <cstdio>
#include <cstdlib>

#include "glutils.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

SceneFlat::SceneFlat() : angle(0.0f)
{
}

void SceneFlat::initScene()
{
    compileAndLinkShader();

    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);

    ogre = new VBOMesh("media/bs_ears.obj");

    view = glm::lookAt(vec3(0.0f,0.35f,0.85f), vec3(0.0f,-0.25f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = mat4(1.0f);

    prog.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Shininess", 100.0f);
}

void SceneFlat::update( float t )
{
    //angle += 1.0f;
    //if( angle > 360.0 ) angle -= 360.0;
}

void SceneFlat::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    vec4 worldLight = vec4(2.0f,4.0f,1.0f,1.0f);
    model = glm::rotate(angle, vec3(0.0f,1.0f,0.0f));
    prog.setUniform("Light.Position", view * model * worldLight );

    model = mat4(1.0f);
    //model *= glm::translate(vec3(0.0,-1.0,0.0));
    model *= glm::rotate(25.0f, vec3(0.0f,1.0f,0.0f));
    //model *= glm::rotate(140.0f, vec3(0.0f,1.0f,0.0f));

    setMatrices();
    ogre->render();
}

void SceneFlat::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneFlat::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(70.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneFlat::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/flat.vert",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/flat.frag",GLSLShader::FRAGMENT))
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

    if( ! prog.validate() )
    {
        printf("Program failed to validate!\n%s",
               prog.log().c_str());
        exit(1);
    }

    prog.use();
}
