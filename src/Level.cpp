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
	SDL_Rect delta = {0, 0, 0, 0};
	if(input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_W) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTY) < -10000)
		delta.y -= 1;
	if(input.getKey(SDL_SCANCODE_DOWN) || input.getKey(SDL_SCANCODE_S) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTY) > 10000)
		delta.y += 1;
	if(input.getKey(SDL_SCANCODE_LEFT) || input.getKey(SDL_SCANCODE_A) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTX) < -10000)
		delta.x -= 1;
	if(input.getKey(SDL_SCANCODE_RIGHT) || input.getKey(SDL_SCANCODE_D) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTX) > 10000)
		delta.x += 1;
	m_character.move(delta);
}