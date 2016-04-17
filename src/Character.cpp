#include "Character.h"

std::ofstream char_log("char_log.txt", std::ofstream::out | std::ofstream::trunc);

Character::Character(SDL_Renderer* const& renderer, const std::string& texturePath) :
	m_renderer(renderer), m_charTexture(NULL),
	m_charAngle(0)
{
	m_charBox = { 150, 150, 32, 32 };

	const bool success = loadTexture(texturePath);
    assert( success );
}

Character::~Character()
{
	char_log << "coucou";
	SDL_DestroyTexture(m_charTexture);
	m_charTexture = NULL;
	char_log << " c'est moi";
}

void Character::draw(SDL_Rect const& camera)
{
	SDL_Rect box = {0, 0, m_charBox.w, m_charBox.h};
	box.x = m_charBox.x - camera.x;
	box.y = m_charBox.y - camera.y;
	SDL_RenderCopyEx(m_renderer, m_charTexture, NULL, &box, m_charAngle, NULL, SDL_FLIP_NONE);
}

void Character::moveX(int x)
{
	m_charBox.x += x;
}

void Character::moveY(int y)
{
	m_charBox.y += y;
}

bool Character::loadTexture(const std::string& texturePath)
{
	SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());
	if(loadedSurface == NULL)
	{
		char_log << "Unable to load image " << texturePath.c_str() << " ! SDL_image Error : " << IMG_GetError() << std::endl;
		return false;
	}
	else
	{
		m_charTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if(m_charTexture == NULL)
		{
			char_log << "Unable to create texture from " << texturePath.c_str() << " ! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_FreeSurface(loadedSurface);
		return true;
	}
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