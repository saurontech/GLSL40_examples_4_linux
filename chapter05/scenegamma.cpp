#include "scenegamma.h"

#include <cstdio>
#include <cstdlib>

#include <QImage>
#include <QGLWidget>

#include "glutils.h"
#include "defines.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/matrix_projection.hpp>

SceneGamma::SceneGamma()
{
    width = 800;
    height = 600;
}

void SceneGamma::initScene()
{
    compileAndLinkShader();

    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glEnable(GL_DEPTH_TEST);

    float c = 2.5f;
    projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f *c, 0.3f*c, 0.1f, 100.0f);

    plane = new VBOPlane(50.0f, 50.0f, 1, 1);
    c = 1.5f;
    torus = new VBOTorus(0.7f * c, 0.3f * c, 50,50);
    ogre = new VBOMesh("mesh/bs_ears.obj");

    angle = PI / 2.0;

    prog.setUniform("Light.Intensity", vec3(1.0f,1.0f,1.0f) );
    prog.setUniform("Gamma",2.2f);
    //prog.setUniform("Gamma",1.0f);
}


void SceneGamma::update( float t )
{
    angle += 0.001f;
    if( angle > TWOPI) angle -= TWOPI;
}

void SceneGamma::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::lookAt(vec3(3.0f * cos(angle),0.0f,3.0f * sin(angle)), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

    prog.setUniform("Light.Position", view * vec4(10.0f,0.0f,0.0f,1.0f) );
    prog.setUniform("Material.Kd", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
    prog.setUniform("Material.Ka", 0.0f, 0.0f, 0.0f);
    prog.setUniform("Material.Shininess", 100.0f);

    model = mat4(1.0f);
    setMatrices();
    ogre->render();

    glFinish();
}

void SceneGamma::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneGamma::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    //projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneGamma::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/gamma.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/gamma.fs",GLSLShader::FRAGMENT))
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
