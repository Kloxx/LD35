#include "SceneOpenGL.h"

std::ofstream log_file("scene_log.txt", std::fstream::out | std::fstream::trunc);

SceneOpenGL::SceneOpenGL(const bool fullscreen) :
	m_window(NULL), m_renderer(NULL), m_GLContext(NULL),
	m_input(), m_fullscreen(fullscreen), m_useJoysticks(false)
{
}

SceneOpenGL::~SceneOpenGL()
{
	m_input.closeGameControllers();
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	SDL_DestroyRenderer(m_renderer);
	m_renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool SceneOpenGL::initWindow(const std::string& windowTitle)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == -1)
	{
		log_file << "SDL could not initialize! SDL_Error : " << SDL_GetError() << std::endl;
		SDL_Quit();
		
		return false;
	}
	
	if(SDL_NumJoysticks())
        m_useJoysticks = true;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	if(m_fullscreen) m_window = SDL_CreateWindow(windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
	else m_window = SDL_CreateWindow(windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
		
	if(m_window == 0)
	{
		log_file << "Window could not be created! SDL_Error : " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		
		return false;
	}
	
	m_GLContext = SDL_GL_CreateContext(m_window);

    if(!m_GLContext)
    {
        log_file << "GLContext could not be created! SDL_Error : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }
	
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if(m_renderer == NULL)
	{
		log_file << "Renderer could not be created! SDL_Error : " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		
		return false;
	}
	
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x15, 0xff);
	if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
	{
		log_file << "SDL_image could not initialize! SDL_image Error : " << IMG_GetError() << std::endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	
	if(TTF_Init() == -1)
	{
		log_file << "SDL_ttf could not initialize! SDL_ttf Error : " << TTF_GetError() << std::endl;
		SDL_Quit();
		IMG_Quit();
		return false;
	}
	
	return true;
}

#ifdef USE_OPENGL_TRUE
bool SceneOpenGL::initGL()
{
    #ifdef WIN32
    GLenum initGLEW( glewInit() );

    if(initGLEW != GLEW_OK)
    {
        log_file << "Error while initializing GLEW : " << glewGetErrorString(initGLEW) << std::endl;
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }
    #endif // WIN32

    glEnable(GL_DEPTH_TEST);

    return true;
}
#endif // USE_OPENGL_TRUE

void SceneOpenGL::mainLoop()
{
	if(m_useJoysticks)
    {
        m_input.openGameControllers();
        //if(!SDL_GameControllerEventState(SDL_ENABLE))
          //  std::cout << SDL_GetError() << std::endl;
    }

	// framerate cap
	const unsigned int frameRate(1000/60);
	
	// start frame count
	int frames = 0;
	const unsigned int startProgram = SDL_GetTicks();
	
    m_input.afficherPtr(true);
    m_input.capturePtr(false);
	
	Character character(m_renderer, "assets/char.png");
	
	// start loop
	while(!m_input.terminate())
	{
		// control framerate
		const unsigned int startLoop = SDL_GetTicks();
		
		// get events
		m_input.updateEvents();
		
		if(m_input.getKey(SDL_SCANCODE_ESCAPE))
			break;
			
		if(m_input.getControllerButton(0, 0))
			break;
		
		// clear screen
		SDL_RenderClear(m_renderer);
		
		// render
		character.draw();
		
		// update screen
		SDL_RenderPresent(m_renderer);
			
		// control framerate
		const unsigned int elapsed = SDL_GetTicks() - startLoop;
		if(elapsed < frameRate) 
			SDL_Delay(frameRate - elapsed);
			frames++;
	}
	const unsigned int stopProgram = SDL_GetTicks();
	
	{	// FPS stats
		const double elapsed = static_cast<double>(stopProgram - startProgram) / 1000;
		const double frameRateAvg = frames/elapsed;
		
		log_file << "Ran for " << elapsed << "s" << std::endl;
		log_file << "Frames : " << frames << std::endl;
		log_file << "Average framerate : " << frameRateAvg << std::endl;
	}
}
	