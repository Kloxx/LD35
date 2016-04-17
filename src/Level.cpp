#include "Level.h"

std::ofstream level_log("level_log.txt", std::ofstream::out | std::ofstream::trunc);

Level::Level(SDL_Renderer* const& renderer) :
	m_character(renderer, "data/assets/char.png"),
	m_npc1(renderer, "data/assets/npc.png", {50, 50, 32, 32}),
	m_floor(renderer, "data/assets/tilesheet.png", "levels/level1.map")
{
	m_camera = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
}

Level::~Level()
{
	level_log << "coucou";
}

void Level::draw()
{
	m_floor.draw(m_camera);
	m_character.draw();
	m_npc1.draw();
}

void Level::control(Input const& input)
{
	float y(0);
	float x(0);
	if(input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_W) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTY) < -10000)
		y -= SPEED;
	if(input.getKey(SDL_SCANCODE_DOWN) || input.getKey(SDL_SCANCODE_S) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTY) > 10000)
		y += SPEED;
	if(input.getKey(SDL_SCANCODE_LEFT) || input.getKey(SDL_SCANCODE_A) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTX) < -10000)
		x -= SPEED;
	if(input.getKey(SDL_SCANCODE_RIGHT) || input.getKey(SDL_SCANCODE_D) || input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTX) > 10000)
		x += SPEED;
	if(x && y)
	{
		float norm = getVectorNorm(x, y);
		x = x * SPEED / norm;
		y = y * SPEED / norm;
	}
		
	SDL_Rect delta = {x, y, 0, 0};
	m_character.move(delta);
}

float Level::getVectorNorm(float x, float y)
{
	return sqrt(x*x + y*y);
}