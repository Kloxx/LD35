#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "common.h"
#include "Input.h"
#include "Character.h"
#include "NPC.h"
#include "Floor.h"

#define SPEED 5

class Level
{
public:
	Level(SDL_Renderer* const& renderer);
	~Level();
	void draw();
	void control(Input const& input);
	void setCamera();

private:
	SDL_Rect m_camera;
	float getVectorNorm(float x, float y);
	Character m_character;
	NPC m_npc1;
	Floor m_floor;
};

#endif // LEVEL_H_INCLUDED