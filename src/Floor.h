#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED

#include "common.h"

#define NUM_TILES_WIDTH 16
#define NUM_TILES_HEIGHT 12
#define TOTAL_TILES 192
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
	void setBox(SDL_Rect& box);
	void setType(int tileType);
	
private:
	SDL_Rect m_box;
	int m_type;
};

class Floor
{
public:
	Floor(SDL_Renderer* const& renderer, std::string const& tileSetPath, 
		std::string const& mapPath);
	~Floor();
	void draw(SDL_Rect& camera);
	
private:
	bool setTiles(std::string const& mapPath);
	bool loadTexture(std::string const& tileSetPath);
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	
	//std::string m_mapData[TOTAL_TILES];
	Tile m_tiles[TOTAL_TILES];
	SDL_Renderer* m_renderer;
	SDL_Texture* m_tileSet;
};

#endif // FLOOR_H_INCLUDED