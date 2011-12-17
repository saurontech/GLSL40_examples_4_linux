#ifndef VBOPLANE_H
#define VBOPLANE_H

#include "drawable.h"

#include <GL/glew.h>
#include <GL/gl.h>

class VBOPlane : public Drawable
{
private:
    GLuint vaoHandle;
    int faces;

public:
    VBOPlane(float, float, int, int);

    void render() const;
};

#endif // VBOPLANE_H
