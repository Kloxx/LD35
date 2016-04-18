#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "common.h"

const int NUMBER_OF_SHAPES = 4;
const int SPRITE_WIDTH = 64;
const int SPRITE_HEIGHT = 205;
const int STARTING_SPRITE[] = {0, 0};
const int NUMBER_OF_FRAMES[] = {1, 4};
enum AnimationStates
{
	CHAR_STILL,
	CHAR_WALKING
};
enum Direction
{
	CHAR_LEFT,
	CHAR_RIGHT,
	CHAR_UP,
	CHAR_DOWN
};

class Character
{
public:
	Character(SDL_Renderer* const& renderer, const std::string& textureFolder);
	~Character();
	void draw(SDL_Rect const& camera);
	void moveX(int x);
	void moveY(int y);
	void shapeShift(int cmd);
	void setDirection(int direction);
	void setState(int m_charState);
	
	SDL_Rect getBox();
	int getX();
	int getY();
	int getW();
	int getH();
	int getShape();

private:
	bool loadTexture(const std::string& textureFolder);

	SDL_Renderer* m_renderer;
	SDL_Texture* m_charTexture[NUMBER_OF_SHAPES];
	SDL_Rect m_charBox;
	SDL_Rect m_charClip;
	int m_charDirection;
	int m_charShape;
	int m_charState;
	int m_frameCount;
};

#endif // CHARACTER_H_INCLUDED