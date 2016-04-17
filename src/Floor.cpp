#include "Floor.h"

std::ofstream floor_log("floor_log.txt", std::ofstream::out | std::ofstream::trunc);

Floor::Floor(SDL_Renderer* const& renderer, std::string const& tileSetPath, 
std::string const& mapPath) :
	m_renderer(renderer), m_tileSet(NULL)
{
	bool success = loadTexture(tileSetPath);
    assert( success );
	success = setTiles(mapPath);
	assert( success );
}

Floor::~Floor()
{
	floor_log << "coucou";
	SDL_DestroyTexture(m_tileSet);
	m_tileSet = NULL;
	floor_log << " c'est moi";
}

bool Floor::loadTexture(std::string const& tileSetPath)
{
	SDL_Surface* loadedSurface = IMG_Load(tileSetPath.c_str());
	if(loadedSurface == NULL)
	{
		floor_log << "Unable to load image " << tileSetPath.c_str() << " ! SDL_image Error : " << IMG_GetError() << std::endl;
		return false;
	}
	m_tileSet = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
	if(m_tileSet == NULL)
	{
		floor_log << "Unable to create texture from " << tileSetPath.c_str() << " ! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FreeSurface(loadedSurface);
	return true;
}

bool Floor::setTiles(std::string const& mapPath)
{
	int x(0), y(0);
	
	std::ifstream map(mapPath.c_str());
	if(map == NULL)
	{
		floor_log << "Unable to load map file " << mapPath.c_str() << std::endl;
		return false;
	}
	
	for(int i(0); i < TOTAL_TILES; i++)
	{
		int tileType = -1;
		std::string tileTypeStr = "";
		
		map >> tileTypeStr;
		if(map.fail())
		{
			floor_log << "Error loading map: Unexpected EoF!" << std::endl;
			return false;
		}
		
		tileType = std::stoi(tileTypeStr, nullptr, 16);
		if((tileType < 0) || (tileType >= TOTAL_TILE_SPRITES))
		{
			floor_log << "Error loading map: Invalid tile type at " << i  << std::endl;
			return false;
		}
		SDL_Rect box = {x*TILE_SIZE_FINAL, y*TILE_SIZE_FINAL, TILE_SIZE_FINAL, TILE_SIZE_FINAL};
		m_tiles[i].setBox(box);
		m_tiles[i].setType(tileType);
		
		x += 1;
		if(x >= NUM_TILES_WIDTH)
		{
			x = 0;
			y += 1;
		}
	}
	map.close();
}

void Floor::draw(SDL_Rect& camera)
{
	for(int i(0); i < TOTAL_TILES; i++)
	{
		SDL_Rect box = m_tiles[i].getBox();
		int tileType = m_tiles[i].getType();
		if(checkCollision(camera, box))
		{
			
			SDL_Rect tile = {tileType%16 * TILE_SIZE, tileType/16 * TILE_SIZE, TILE_SIZE, TILE_SIZE};
			box.x = box.x - camera.x;
			box.y = box.y - camera.y;
			SDL_RenderCopy(m_renderer, m_tileSet, &tile, &box);
		}
	}
}

bool Floor::checkCollision(SDL_Rect a, SDL_Rect b)
{
	return SDL_HasIntersection(&a, &b);
}

Tile::Tile() :
	m_type(0)
{
	m_box = {0, 0, 32, 32};
}

Tile::Tile(int x, int y, int tileType) :
	m_type(tileType)
{
	m_box.x = x;
	m_box.y = y;
	m_box.w = 32;
	m_box.h = 32;
}

Tile::~Tile()
{
}

Tile Tile::operator=(Tile* tile)
{
	Tile newTile;
	newTile.m_box = tile->m_box;
	newTile.m_type = tile->m_type;
	floor_log << tile->m_box.y << " , " << newTile.m_box.y << std::endl;
	return newTile;
}

SDL_Rect Tile::getBox()
{
	return m_box;
}

int Tile::getType()
{
	return m_type;
}

void Tile::setBox(SDL_Rect& box)
{
	m_box = box;
}

void Tile::setType(int tileType)
{
	m_type = tileType;
}