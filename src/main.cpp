#include <iostream>
#include "SceneOpenGL.h"

int main(int argc, char **argv)
{
	SceneOpenGL scene(false);
	
	if(!scene.initWindow("LD35 - Shapeshift")) 
		return -1;
	
    if(!scene.initGL()) 
		return -1;
	
	scene.mainLoop();
	
	return 0;
}