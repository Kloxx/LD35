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
	void getPosition();

private:
	bool loadTexture(const std::string& texturePath);

	SDL_Renderer* m_renderer;
	SDL_Texture* m_charTexture;
	SDL_Rect m_charPos;
	float m_charAngle;
};

#endif // CHARACTER_H_INCLUDED