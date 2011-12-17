#ifndef VBOMESH_H
#define VBOMESH_H

#include "drawable.h"

#include <vector>
using std::vector;
#include <glm/glm.hpp>
using glm::vec3;
using glm::vec2;
using glm::vec4;

#include <string>
using std::string;

class VBOMesh : public Drawable
{
private:
    unsigned int faces;
    unsigned int vaoHandle;

    void trimString( string & str );
    void storeVBO( const vector<vec3> & points,
                            const vector<vec3> & normals,
                            const vector<vec2> &texCoords,
                            const vector<vec4> &tangents,
                            const vector<int> &elements );
public:
    VBOMesh( const char * fileName );

    void render() const;

    void loadOBJ( const char * fileName );
};

#endif // VBOMESH_H
