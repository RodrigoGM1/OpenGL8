#ifndef LOADSHADERS_H
#define LOADSHADERS_H

#include <GL/gl.h>

typedef struct LoadShaders {
    GLenum      type;
    const char* filename;
    GLuint      shader;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo*);


#endif /* LOADSHADERS_H */