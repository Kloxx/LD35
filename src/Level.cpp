#include "Level.h"

std::ofstream level_log("level_log.txt", std::ofstream::out | std::ofstream::trunc);

Level::Level(SDL_Renderer* const& renderer) :
	m_character(renderer, "assets/char.png")
{
}

Level::~Level()
{
}

void Level::draw()
{
	m_character.draw();
}

void Level::control(Input const& input)
{
	float y(0);
	float x(0);
	if(input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_W) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTY) < -10000)
		y -= 5;
	if(input.getKey(SDL_SCANCODE_DOWN) || input.getKey(SDL_SCANCODE_S) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTY) > 10000)
		y += 5;
	if(input.getKey(SDL_SCANCODE_LEFT) || input.getKey(SDL_SCANCODE_A) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTX) < -10000)
		x -= 5;
	if(input.getKey(SDL_SCANCODE_RIGHT) || input.getKey(SDL_SCANCODE_D) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTX) > 10000)
		x += 5;
	if(x && y)
	{
		float norm = getVectorNorm(x, y);
		x = x/norm*5;
		y = y/norm*5;
	}
		
	SDL_Rect delta = {x, y, 0, 0};
	m_character.move(delta);
}

float Level::getVectorNorm(float x, float y)
{
	return sqrt(x*x + y*y);
}