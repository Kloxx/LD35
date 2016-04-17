#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED

#include "common.h"

#define MAX_TILES 1024
#define TOTAL_TILE_SPRITES 256

#define TILE_SIZE 32
#define TILE_SIZE_FINAL 96

class Tile
{
public:
	Tile();
	Tile(int x, int y, int tileType);
	~Tile();
	Tile operator=(Tile* tile);
	int getType();
	SDL_Rect getBox();
	bool isVisible();
	int getHeight();
	void setBox(SDL_Rect& box);
	void setType(int tileType);
	void setVisible(bool isVisible);
	void changeHeight(int y);
	
private:
	SDL_Rect m_box;
	int m_type;
	bool m_isVisible;
	int m_height;
};

class Floor
{
public:
	Floor(SDL_Renderer* const& renderer, std::string const& tileSetPath, 
		std::string const& mapPath);
	~Floor();
	void draw(SDL_Rect const& camera, SDL_Rect const& character);
	bool touchesWall(SDL_Rect box);
	SDL_Point getLevelSize();
	
private:
	bool setTiles();
	bool loadTexture(std::string const& tileSetPath);
	bool checkCollision(SDL_Rect const& a, SDL_Rect const& b);
	int getDistance(SDL_Rect const& a, SDL_Rect const& b);
	
	std::ifstream m_mapData;
	int m_levelWidth, m_levelHeight;
	SDL_Point m_levelSize;
	int m_totalTiles;
	Tile m_tiles[MAX_TILES];
		
	SDL_Renderer* m_renderer;
	SDL_Texture* m_tileSet;
};

#endif // FLOOR_H_INCLUDED