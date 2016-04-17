#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "common.h"

class Character
{
public:
	Character(SDL_Renderer* const& renderer, const std::string& texturePath);
	~Character();
	void draw();
	void move(SDL_Rect &delta);
	SDL_Rect getBox();

private:
	bool loadTexture(const std::string& texturePath);

	SDL_Renderer* m_renderer;
	SDL_Texture* m_charTexture;
	SDL_Rect m_charBox;
	float m_charAngle;
};

#endif // CHARACTER_H_INCLUDED