#include "Character.h"

std::ofstream char_log("char_log.txt", std::ofstream::out | std::ofstream::trunc);

Character::Character(SDL_Renderer* const& renderer, const std::string& texturePath) :
	m_renderer(renderer), m_charTexture(NULL),
	m_charAngle(0)
{
	m_charPos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 32, 32 };

	const bool success = loadTexture(texturePath);
    assert( success );
}

Character::~Character()
{
	SDL_DestroyTexture(m_charTexture);
	m_charTexture = NULL;
}

void Character::control(Input const& m_input)
{
}

void Character::draw()
{
	SDL_RenderCopyEx(m_renderer, m_charTexture, NULL, &m_charPos, m_charAngle, NULL, SDL_FLIP_NONE);
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