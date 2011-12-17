#include "sceneparticlesinstanced.h"

#include <cstdio>
#include <cstdlib>

#include <QImage>
#include <QGLWidget>

#include "glutils.h"
#include "defines.h"

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

SceneParticlesInstanced::SceneParticlesInstanced()
{
    width = 800;
    height = 600;
    time = 0.0f;
    deltaT = 0.0f;
}

void SceneParticlesInstanced::initScene()
{    
    compileAndLinkShader();

    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glEnable(GL_DEPTH_TEST);

    plane = new VBOPlane(13.0f, 10.0f, 200, 2);
    float c = 0.15f;
    torus = new VBOTorus(0.7f * c, 0.3f * c, 20, 20);
    projection = mat4(1.0f);

    angle = PI / 2.0f;
    model = mat4(1.0f);

    initBuffers();

    prog.setUniform("Light.Intensity", vec3(1.0f,1.0f,1.0f) );
    prog.setUniform("ParticleLifetime", 3.5f);
    prog.setUniform("Gravity", vec3(0.0f,-0.2f,0.0f));
}

void SceneParticlesInstanced::initBuffers()
{
    nParticles = 500;

    // Generate the buffers
    glGenBuffers(1, &initVel);   // Initial velocity buffer
    glGenBuffers(1, &startTime); // Start time buffer

    // Allocate space for all buffers
    int size = nParticles * 3 * sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, initVel);
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, startTime);
    glBufferData(GL_ARRAY_BUFFER, nParticles * sizeof(float), NULL, GL_STATIC_DRAW);

    // Fill the first velocity buffer with random velocities
    vec3 v(0.0f);
    float velocity, theta, phi;
    GLfloat *data = new GLfloat[nParticles * 3];
    for( uint i = 0; i < nParticles; i++ ) {

        theta = glm::mix(0.0f, (float)PI / 6.0f, randFloat());
        phi = glm::mix(0.0f, (float)TWOPI, randFloat());

        v.x = sinf(theta) * cosf(phi);
        v.y = cosf(theta);
        v.z = sinf(theta) * sinf(phi);

        velocity = glm::mix(1.25f,1.5f,randFloat());
        v = glm::normalize(v) * velocity;

        data[3*i]   = v.x;
        data[3*i+1] = v.y;
        data[3*i+2] = v.z;
    }
    glBindBuffer(GL_ARRAY_BUFFER,initVel);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

    // Fill the start time buffer
    delete [] data;
    data = new GLfloat[nParticles];
    float time = 0.0f;
    float rate = 0.01f;
    for( int i = 0; i < nParticles; i++ ) {
        data[i] = time;
        time += rate;
    }
    glBindBuffer(GL_ARRAY_BUFFER,startTime);
    glBufferSubData(GL_ARRAY_BUFFER, 0, nParticles * sizeof(float), data);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    delete [] data;

    // Attach these to the torus's vertex array
    glBindVertexArray(torus->getVertexArrayHandle());
    glBindBuffer(GL_ARRAY_BUFFER, initVel);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, startTime);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(4);

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);

}

float SceneParticlesInstanced::randFloat() {
    return ((float)rand() / RAND_MAX);
}

void SceneParticlesInstanced::update( float t )
{
    deltaT = t - time;
    time = t;
}

void SceneParticlesInstanced::render()
{
    prog.setUniform("Time", time);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::lookAt(vec3(3.0f * cos(angle),1.5f,3.0f * sin(angle)), vec3(0.0f,1.5f,0.0f), vec3(0.0f,1.0f,0.0f));

    prog.setUniform("Light.Position", vec4(0.0f,0.0f,0.0f,1.0f) );
    prog.setUniform("Material.Kd", 0.9f, 0.5f, 0.2f);
    prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 100.0f);
    model = mat4(1.0f);
    setMatrices();

    glBindVertexArray(torus->getVertexArrayHandle());
    glDrawElementsInstanced(GL_TRIANGLES, 6 * 20 * 20, GL_UNSIGNED_INT, 0, nParticles);
}

void SceneParticlesInstanced::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("ProjectionMatrix", projection);
    //prog.setUniform("MVP", projection * mv);
}

void SceneParticlesInstanced::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(60.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneParticlesInstanced::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("shader/particleinstanced.vs",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/particleinstanced.fs",GLSLShader::FRAGMENT))
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
