#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "common.h"
#include "Input.h"
#include "Character.h"

class Level
{
public:
	Level(SDL_Renderer* const& renderer);
	~Level();
	void draw();
	void control(Input const& input);

private:
	float getVectorNorm(float x, float y);
	Character m_character;
};

#endif // LEVEL_H_INCLUDED