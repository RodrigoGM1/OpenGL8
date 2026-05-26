#include <cstdlib>
#include <iostream>

#include <GLES3/gl3.h>
#include "../include/CargarShader.h"

const GLchar* LeerShader(const char* archivo)
{
#ifdef WIN32
    FILE* archivoEntrada;
    fopen_s(&archivoEntrada, archivo, "rb");
#else
    FILE* archivoEntrada = fopen(archivo, "rb");
#endif

    if(!archivoEntrada){
#ifdef _DEBUG
        std::cerr<<"Archivo no encontrado "<< archivo <<std::endl;
#endif
        return NULL;
    }

    fseek(archivoEntrada, 0, SEEK_END);
    int len = ftell(archivoEntrada);
    fseek(archivoEntrada, 0, SEEK_SET);

    GLchar* codigo = new GLchar[len+1];

    fread(codigo, 1, len, archivoEntrada);
    fclose(archivoEntrada);

    codigo[len] = 0;

    return const_cast<const GLchar*>(codigo);
}

GLuint CargarShaders(ShaderInfo* shaders)
{
    GLuint programa = glCreateProgram();

    ShaderInfo* entrada = shaders;
    while(entrada->tipo != GL_NONE){
        GLuint shader = glCreateShader(entrada->tipo);

        entrada->shader = shader;

        const GLchar* codigo = LeerShader(entrada->archivo);
        if(codigo == NULL){
            for(entrada = shaders; entrada->tipo != GL_NONE; ++entrada){
                glDeleteShader(entrada->shader);
                entrada->shader = 0;
            }

            return 0;
        }

        glShaderSource(shader, 1, &codigo, NULL);
        delete[] codigo;

        glCompileShader(shader);

        GLint compilar;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compilar);
        if(!compilar){
#ifdef _DEBUG
            GLsizei len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
            GLchar* log = new GLchar[len+1];
            glGetShaderInfoLog( shader, len, &len, log );
            std::cerr << "Shader compilacion fallida: " << log << std::endl;
            delete [] log;
#endif
            return 0;
        }

        glAttachShader(programa, shader);

        ++entrada;
    }

    glLinkProgram(programa);

    GLint linked;
    glGetProgramiv(programa, GL_LINK_STATUS, &linked);
    if(!linked){
#ifdef _DEBUG
        GLsizei len;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog( program, len, &len, log );
        std::cerr << "Shader linkeo falido: " << log << std::endl;
        delete [] log;
#endif
        for(entrada = shaders; entrada->tipo != GL_NONE; ++entrada){
            glDeleteShader(entrada->shader);
            entrada->shader = 0;
        }

        return 0;
    }

    return programa;
}