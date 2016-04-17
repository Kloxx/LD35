#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "common.h"

class NPC
{
public:
	NPC(SDL_Renderer* const& renderer, const std::string& texturePath, SDL_Rect position);
	~NPC();
	void draw();
	void move(SDL_Rect &delta);
	SDL_Rect getPosition();
	
private:
	bool loadTexture(const std::string& texturePath);

	SDL_Renderer* m_renderer;
	SDL_Texture* m_npcTexture;
	SDL_Rect m_npcPos;
	float m_npcAngle;
};

#endif // NPC_H_INCLUDED