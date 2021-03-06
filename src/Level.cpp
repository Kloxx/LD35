#include "Level.h"

std::ofstream level_log("level_log.txt", std::ofstream::out | std::ofstream::trunc);

Level::Level(SDL_Renderer* const& renderer) :
	m_character(renderer, "data/assets/char/"),
	m_npc1(renderer, "data/assets/npc.png", {50, 50, 32, 32}),
	m_floor(renderer, "data/assets/tilesheet2.png", "data/levels/level1.map"),
	m_currentButtonDown(NULL)
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
	m_npc1.draw(m_camera);
}

void Level::control(Input const& input)
{
	// direction
	float y(0);
	float x(0);
	float yaxis(input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTY));
	float xaxis(input.getControllerAxis(JOY0, SDL_CONTROLLER_AXIS_LEFTX));
	if(input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_W))
		y -= SPEED;
	if(input.getKey(SDL_SCANCODE_DOWN) || input.getKey(SDL_SCANCODE_S))
		y += SPEED;
	if(input.getKey(SDL_SCANCODE_LEFT) || input.getKey(SDL_SCANCODE_A))
		x -= SPEED;
	if(input.getKey(SDL_SCANCODE_RIGHT) || input.getKey(SDL_SCANCODE_D))
		x += SPEED;
		
	if(yaxis < -5000 || yaxis > 5000)
		y += SPEED * yaxis / 32768;
	if(xaxis < -5000 || xaxis > 5000)
		x += SPEED * xaxis / 32768;
	
	if(x && y)
	{
		float norm = getVectorNorm(x, y);
		x = round(x * SPEED / norm);
		y = round(y * SPEED / norm);
	}
	
	if(!x && !y)
	{
		m_character.setState(CHAR_STILL);
	}
	
	if(x || y)
	{
		m_character.setState(CHAR_WALKING);
	}
	
	if(x > 0)
		m_character.setDirection(CHAR_RIGHT);
	if(x < 0)
		m_character.setDirection(CHAR_LEFT);
	
	if(input.getKey(SDL_SCANCODE_SPACE) || input.getControllerButton(JOY0, SDL_CONTROLLER_BUTTON_A))
	{
		y *= 2;
		x *= 2;
	}
	
	m_character.moveX(x);
	if(m_floor.touchesWall(m_character.getBox()))
		m_character.moveX(-x);
	
	
	m_character.moveY(y);
	if(m_floor.touchesWall(m_character.getBox()))
		m_character.moveY(-y);
		
	// shapeshift
	if(input.getKey(SDL_SCANCODE_1))
		m_character.shapeShift(SHAPE_1);
	if(input.getKey(SDL_SCANCODE_2))
		m_character.shapeShift(SHAPE_2);
	if(input.getKey(SDL_SCANCODE_3))
		m_character.shapeShift(SHAPE_3);
	if(input.getKey(SDL_SCANCODE_4))
		m_character.shapeShift(SHAPE_4);
	if(input.getControllerButton(JOY0, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) && m_currentButtonDown == NULL)
	{
		m_character.shapeShift(SHAPE_PREV);
		m_currentButtonDown = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
	}
	if(input.getControllerButton(JOY0, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) && m_currentButtonDown == NULL)
	{
		m_character.shapeShift(SHAPE_NEXT);
		m_currentButtonDown = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
	}
	if(!input.getControllerButton(JOY0, m_currentButtonDown))
		m_currentButtonDown = NULL;
}

void Level::setCamera()
{
	SDL_Point levelSize = m_floor.getLevelSize();
	int distX = (m_character.getX() + m_character.getW()/2) - WINDOW_WIDTH/2 - m_camera.x;
	int distY = (m_character.getY() + m_character.getH()/2) - WINDOW_HEIGHT/2 - m_camera.y;
	
	//m_camera.x = (m_character.getX() + m_character.getW() / 2) - WINDOW_WIDTH/2;
	m_camera.x += distX/30;
	
	if(m_camera.x < 0)
		m_camera.x = 0;
	if(m_camera.x > levelSize.x - m_camera.w)
		m_camera.x = levelSize.x - m_camera.w;
	
	//m_camera.y = (m_character.getY() + m_character.getH() / 2) - WINDOW_HEIGHT/2;
	m_camera.y += distY/30;
	
	if(m_camera.y < 0)
		m_camera.y = 0;
	if(m_camera.y > levelSize.y - m_camera.h)
		m_camera.y = levelSize.y - m_camera.h;
}

float Level::getVectorNorm(float x, float y)
{
	return sqrt(x*x + y*y);
}