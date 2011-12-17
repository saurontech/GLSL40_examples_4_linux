#include "scenerendertotex.h"

#include <cstdio>
#include <cstdlib>

#include <QImage>
#include <QGLWidget>

#include "glutils.h"
#include "defines.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

SceneRenderToTex::SceneRenderToTex()
{
}

void SceneRenderToTex::initScene()
{
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);

    plane = new VBOPlane(50.0f, 50.0f, 1, 1);
    cube = new VBOCube();

    projection = mat4(1.0f);

    teapot = new VBOTeapot(14, mat4(1.0f));

    angle = 0.0;

    prog.setUniform("Light.Intensity", vec3(1.0f,1.0f,1.0f) );
    setupFBO();

    // One pixel white texture
    GLuint whiteTexHandle;
    GLubyte whiteTex[] = { 255, 255, 255, 255 };
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &whiteTexHandle);
    glBindTexture(GL_TEXTURE_2D,whiteTexHandle);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,whiteTex);
}

void SceneRenderToTex::setupFBO() {
    // Generate and bind the framebuffer
    glGenFramebuffers(1, &fboHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

    // Create the texture object
    GLuint renderTex;
    glGenTextures(1, &renderTex);
    glActiveTexture(GL_TEXTURE0);  // Use texture unit 0
    glBindTexture(GL_TEXTURE_2D, renderTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,512,512,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind the texture to the FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTex, 0);

    // Create the depth buffer
    GLuint depthBuf;
    glGenRenderbuffers(1, &depthBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);

    // Bind the depth buffer to the FBO
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, depthBuf);

    // Set the targets for the fragment output variables
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    // Unbind the framebuffer, and revert to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneRenderToTex::update( float t )
{
    angle += 0.0005f;
    if( angle > TWOPI) angle -= TWOPI;
}

void SceneRenderToTex::render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
    renderToTexture();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    renderScene();
}

void SceneRenderToTex::renderToTexture() {
    prog.setUniform("RenderTex", 1);
    glViewport(0,0,512,512);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::lookAt(vec3(0.0f,0.0f,7.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = glm::perspective(60.0f, 1.0f, 0.3f, 100.0f);

    prog.setUniform("Light.Position", vec4(0.0f,0.0f,0.0f,1.0f) );
    prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 100.0f);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f,-1.5f,0.0f));
    model = glm::rotate(model, -90.0f, vec3(1.0f,0.0f,0.0f));
    setMatrices();
    teapot->render();
}

void SceneRenderToTex::renderScene() {
    prog.setUniform("RenderTex", 0);
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3 cameraPos = vec3(2.0f * cos(angle), 1.5f, 2.0f * sin(angle));
    view = glm::lookAt(cameraPos, vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

    projection = glm::perspective(45.0f, (float)width/height, 0.3f, 100.0f);

    prog.setUniform("Light.Position", vec4(0.0f,0.0f,0.0f,1.0f) );
    prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 0.0f);

    model = mat4(1.0f);
    setMatrices();
    cube->render();
}

void SceneRenderToTex::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneRenderToTex::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneRenderToTex::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/rendertotex.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/rendertotex.fs",GLSLShader::FRAGMENT))
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
