#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#define USE_OPENGL_TRUE
#define NDEBUG

// OpenGL
#ifdef USE_OPENGL_TRUE
#ifdef WIN32
#include <GL/glew.h>
#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#else
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#endif
#endif // USE_OPENGL_TRUE

// GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

// std library
#include <string>
#include <fstream>

// other
#include <assert.h>

// options
#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900


#endif // COMMON_H_INCLUDED