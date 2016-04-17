#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "common.h"

class Character
{
public:
	Character(SDL_Renderer* const& renderer, const std::string& texturePath);
	~Character();
	void draw(SDL_Rect const& camera);
	void moveX(int x);
	void moveY(int y);
	
	SDL_Rect getBox();
	int getX();
	int getY();
	int getW();
	int getH();

private:
	bool loadTexture(const std::string& texturePath);

	SDL_Renderer* m_renderer;
	SDL_Texture* m_charTexture;
	SDL_Rect m_charBox;
	float m_charAngle;
};

#endif // CHARACTER_H_INCLUDED