#define GL_GLEXT_PROTOTYPES
#define BUFFER_OFFSET(offset) ((void*)(offset))

#include <GL/gl.h>
#include <SDL3/SDL.h>

#include "include/CargarShader.h"

void init(void);
void mostrar(void);


enum VAO_IDs { Triangulos, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosicion = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

int main(int argc, char** argv)
{
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("No se pudo iniciar SDL: %s", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window* ventana = SDL_CreateWindow("Ventana SDL3", 512, 512, SDL_WINDOW_OPENGL);
    if(!ventana){
        SDL_Log("No se pudo crear la ventana: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_GLContext contexto = SDL_GL_CreateContext(ventana);
    if(!contexto){
        SDL_Log("No se pudo crear el contexto OpenGL: %s", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return -1;
    }

    init();

    bool run = true;
    SDL_Event evento;
    while(run){
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_EVENT_QUIT){ run = false; }
        }

        mostrar();

        SDL_GL_SwapWindow(ventana);
    }

    SDL_GL_DestroyContext(contexto);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}

void init(void)
{
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangulos]);

    GLfloat vertices[NumVertices][2] = {
        { -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },
        {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER,   "shader/triangulos.vert"},
        {GL_FRAGMENT_SHADER, "shader/triangulos.frag"},
        {GL_NONE, NULL}
    };

    GLuint programa = CargarShaders(shaders);
    glUseProgram(programa);

    glVertexAttribPointer(vPosicion, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosicion);
}

void mostrar(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAOs[Triangulos]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    glFlush();
}