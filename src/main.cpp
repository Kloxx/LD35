#include <iostream>
#include "SceneOpenGL.h"

int main(int argc, char **argv)
{
	SceneOpenGL scene(false);
	
	if(!scene.initWindow("LD35 - Shapeshift")) 
		return -1;
	
	#ifdef USE_OPENGL_TRUE
    if(!scene.initGL()) 
		return -1;
	#endif // USE_OPENGL_TRUE
	
	scene.mainLoop();
	
	return 0;
}