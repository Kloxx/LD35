#include "Level.h"

std::ofstream level_log("level_log.txt", std::ofstream::out | std::ofstream::trunc);

Level::Level(SDL_Renderer* const& renderer) :
	m_character(renderer, "data/assets/char.png"),
	m_npc1(renderer, "data/assets/npc.png", {50, 50, 32, 32}),
	m_floor(renderer, "data/assets/tilesheet2.png", "data/levels/level1.map")
{
	m_camera = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
}

Level::~Level()
{
	level_log << "coucou";
}

void Level::draw()
{
	setCamera();
	m_floor.draw(m_camera, m_character.getBox());
	m_character.draw(m_camera);
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
		x = round(x * SPEED / norm);
		y = round(y * SPEED / norm);
	}
	
	m_character.moveX(x);
	if(m_floor.touchesWall(m_character.getBox()))
		m_character.moveX(-x);
	
	
	m_character.moveY(y);
	if(m_floor.touchesWall(m_character.getBox()))
		m_character.moveY(-y);
}

void Level::setCamera()
{
	m_camera.x = (m_character.getX() + m_character.getW() / 2) - WINDOW_WIDTH/2;
	if(m_camera.x < 0)
		m_camera.x = 0;
	m_camera.y = (m_character.getY() + m_character.getH() / 2) - WINDOW_HEIGHT/2;
	if(m_camera.y < 0)
		m_camera.y = 0;
}

float Level::getVectorNorm(float x, float y)
{
	return sqrt(x*x + y*y);
}