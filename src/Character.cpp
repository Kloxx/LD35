#include "Character.h"

std::ofstream char_log("char_log.txt", std::ofstream::out | std::ofstream::trunc);

Character::Character(SDL_Renderer* const& renderer, const std::string& textureFolder) :
	m_renderer(renderer),
	m_charDirection(CHAR_UP), m_charShape(SHAPE_1)
{
	m_charBox = {300, 300, SPRITE_WIDTH, SPRITE_HEIGHT};
	m_charClip = {0, 0, SPRITE_WIDTH, SPRITE_HEIGHT};
	
	for(int i(0); i<4; i++)
		m_charTexture[i] = NULL;

	const bool success = loadTexture(textureFolder);
    assert( success );
}

Character::~Character()
{
	char_log << "coucou";
	for(int i(0); i<4; i++)
	{
		m_charTexture[i] = NULL;
		SDL_DestroyTexture(m_charTexture[i]);
	}
	char_log << " c'est moi";
}

void Character::draw(SDL_Rect const& camera)
{
	SDL_Rect box = {0, 0, m_charBox.w, m_charBox.h};
	box.x = m_charBox.x - camera.x;
	box.y = m_charBox.y - camera.y;
	m_charClip.x = STARTING_SPRITE[m_charState] + (m_frameCount/ANIMATION_FRAMES) % NUMBER_OF_FRAMES[m_charState] * SPRITE_WIDTH;
	SDL_RenderCopy(m_renderer, m_charTexture[m_charShape], &m_charClip, &box);
	m_frameCount++;
}

void Character::moveX(int x)
{
	m_charBox.x += x;
}

void Character::moveY(int y)
{
	m_charBox.y += y;
}

void Character::shapeShift(int cmd)
{
	switch(cmd)
	{
	case SHAPE_NEXT:
		m_charShape += 1;
		break;
	case SHAPE_PREV:
		m_charShape -= 1;
		break;
	default:
		m_charShape = cmd;
		break;
	}
	if(m_charShape>3)
		m_charShape = 0;
	if(m_charShape<0)
		m_charShape = 3;
	char_log << m_charShape;
}

void Character::setDirection(int direction)
{
	m_charDirection = direction;
	m_charClip.y = direction * SPRITE_HEIGHT;
}

void Character::setState(int state)
{
	if(m_charState != state)
	{
		m_frameCount = 0;
		m_charState = state;
		m_charClip.x = STARTING_SPRITE[state] * SPRITE_WIDTH;
	}
}

bool Character::loadTexture(const std::string& textureFolder)
{
	SDL_Surface* loadedSurface;
	std::string path[4];
	path[0] = textureFolder + "char1.png";
	path[1] = textureFolder + "char2.png";
	path[2] = textureFolder + "char3.png";
	path[3] = textureFolder + "char4.png";
	for(int i(0); i<4; i++)
	{
		loadedSurface = IMG_Load(path[i].c_str());
		if(loadedSurface == NULL)
		{
			char_log << "Unable to load image " << path[i].c_str() << " ! SDL_image Error : " << IMG_GetError() << std::endl;
			return false;
		}
		m_charTexture[i] = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if(m_charTexture[i] == NULL)
		{
			char_log << "Unable to create texture from " << path[i].c_str() << " ! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
	}
	SDL_FreeSurface(loadedSurface);
	return true;
}

SDL_Rect Character::getBox()
{
	return m_charBox;
}

int Character::getX()
{
	return m_charBox.x;
}

int Character::getY()
{
	return m_charBox.y;
}

int Character::getW()
{
	return m_charBox.w;
}

int Character::getH()
{
	return m_charBox.h;
}

int Character::getShape()
{
	return m_charShape;
}