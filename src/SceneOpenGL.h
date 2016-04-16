#ifndef SCENEOPENGL_H_INCLUDED
#define SCENEOPENGL_H_INCLUDED

#include "common.h"

#include "Level.h"
#include "Input.h"

class SceneOpenGL
{
public:
	SceneOpenGL(const bool fullscreen);
	~SceneOpenGL();

	bool initWindow(const std::string& windowTitle);
	bool initGL();
	void mainLoop();

private:
	const bool m_fullscreen;

	SDL_Window* m_window;
	SDL_GLContext m_GLContext;
	SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;
	Input m_input;
	bool m_useJoysticks;
};

#endif // SCENEOPENGL_H_INCLUDED
