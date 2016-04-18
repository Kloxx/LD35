#include "NPC.h"

std::ofstream npc_log("npc_log.txt", std::ofstream::out | std::ofstream::trunc);

NPC::NPC(SDL_Renderer* const& renderer, const std::string& texturePath, SDL_Rect position) :
	m_renderer(renderer), m_npcTexture(NULL),
	m_npcAngle(0), m_npcBox(position)
{
	const bool success = loadTexture(texturePath);
    assert( success );
}

NPC::~NPC()
{
	npc_log << "coucou";
	SDL_DestroyTexture(m_npcTexture);
	m_npcTexture = NULL;
	npc_log << " c'est moi";
}

void NPC::draw(SDL_Rect const& camera)
{
	SDL_Rect box = {0, 0, m_npcBox.w, m_npcBox.h};
	box.x = m_npcBox.x - camera.x;
	box.y = m_npcBox.y - camera.y;
	SDL_RenderCopy(m_renderer, m_npcTexture, NULL, &box);
}

void NPC::move(SDL_Rect &delta)
{
	m_npcBox.x += delta.x;
	m_npcBox.y += delta.y;
}

bool NPC::loadTexture(const std::string& texturePath)
{
	SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());
	if(loadedSurface == NULL)
	{
		npc_log << "Unable to load image " << texturePath.c_str() << " ! SDL_image Error : " << IMG_GetError() << std::endl;
		return false;
	}
	else
	{
		m_npcTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if(m_npcTexture == NULL)
		{
			npc_log << "Unable to create texture from " << texturePath.c_str() << " ! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}
		SDL_FreeSurface(loadedSurface);
		return true;
	}
}

SDL_Rect NPC::getPosition()
{
	return m_npcBox;
}