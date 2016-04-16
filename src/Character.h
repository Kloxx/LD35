#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "common.h"

#include "Input.h"

class Character
{
public:
	Character(SDL_Renderer* const& renderer, const std::string& texturePath);
	~Character();
	void control(Input const& input);
	void draw();

private:
	bool loadTexture(const std::string& texturePath);

	SDL_Renderer* m_renderer;
	SDL_Texture* m_charTexture;
	SDL_Rect m_charPos;
	float m_charAngle;
};

#endif // CHARACTER_H_INCLUDED