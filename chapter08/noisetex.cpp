#include "noisetex.h"

#include <cstdio>

#include <noise/noise.h>

#include <glm/glm.hpp>

int NoiseTex::generate2DTex(bool seamless, float baseFreq, int w, int h) {

    int width = w;
    int height = h;

    noise::module::Perlin perlinNoise;

    // Base frequency for octave 1.
    perlinNoise.SetFrequency(baseFreq);

    printf("Generating noise texture...");

    GLubyte *data = new GLubyte[ width * height * 4 ];

    double xRange = 1.0;
    double yRange = 1.0;
    double xFactor = xRange / width;
    double yFactor = yRange / height;
    for( int oct = 0; oct < 4; oct++ ) {

        perlinNoise.SetOctaveCount(oct+1);

        for( int i = 0; i < width; i++ ) {
            for( int j = 0 ; j < height; j++ ) {
                double x = xFactor * i;
                double y = yFactor * j;
                double z = 0.0;

                float val = 0.0f;
                if( !seamless ) {
                    val = perlinNoise.GetValue(x,y,z);
                } else {
                    double a, b, c, d;

                    a = perlinNoise.GetValue(x         , y       , z);
                    b = perlinNoise.GetValue(x + xRange, y       , z);
                    c = perlinNoise.GetValue(x         , y + yRange, z);
                    d = perlinNoise.GetValue(x + xRange, y + yRange, z);

                    double xmix = 1.0 - x / xRange;
                    double ymix = 1.0 - y / yRange;
                    double x1 = glm::mix( a, b, xmix );
                    double x2 = glm::mix( c, d, xmix );

                    val = glm::mix(x1, x2, ymix );
                }
                // Scale to roughly between 0 and 1
                val = (val + 1.0f) * 0.5f;

                // Clamp strictly between 0 and 1
                val = val > 1.0 ? 1.0 : val;
                val = val < 0.0 ? 0.0 : val;

                // Store in texture
                data[((j * width + i) * 4) + oct] = (GLubyte) ( val * 255.0f );
            }
        }
    }

    GLuint texID;
    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    delete [] data;

    printf("done.\n");
    return texID;
}
