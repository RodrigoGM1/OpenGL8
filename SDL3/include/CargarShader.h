#ifndef _CARGADRO_SHADER_H
#define _CARGADRO_SHADER_H

#include <GL/gl.h>

typedef struct LoadShaders {
    GLenum      tipo;
    const char* archivo;
    GLuint      shader;
} ShaderInfo;

GLuint CargarShaders(ShaderInfo*);


#endif /* _CARGADRO_SHADER_H */