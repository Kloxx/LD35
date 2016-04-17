#include "Floor.h"

std::ofstream floor_log("floor_log.txt", std::ofstream::out | std::ofstream::trunc);

Floor::Floor(SDL_Renderer* const& renderer, std::string const& tileSetPath, 
std::string const& mapPath) :
	m_renderer(renderer), m_tileSet(NULL), m_mapData(mapPath.c_str()), m_totalTiles(0)
{
	bool success = loadTexture(tileSetPath);
    assert( success );
	success = setTiles();
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

bool Floor::setTiles()
{
	int x(0), y(0);
	
	if(m_mapData == NULL)
	{
		floor_log << "Unable to load map file !" << std::endl;
		return false;
	}
	m_mapData >> m_levelWidth;
	m_mapData >> m_levelHeight;
	m_totalTiles = m_levelHeight * m_levelWidth;
	
	for(int i(0); i < m_totalTiles; i++)
	{
		int tileType = -1;
		std::string tileTypeStr = "";
		
		m_mapData >> tileTypeStr;
		if(m_mapData.fail())
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
		if(x >= m_levelWidth)
		{
			x = 0;
			y += 1;
		}
	}
	m_mapData.close();
}

void Floor::draw(SDL_Rect const& camera, SDL_Rect const& character)
{
	for(int i(0); i < m_totalTiles; i++)
	{
		SDL_Rect box = m_tiles[i].getBox();
		int tileType = m_tiles[i].getType();
		if(getDistance(character, box) < 400)
		{
			m_tiles[i].setVisible(true);
			m_tiles[i].changeHeight(20);
			SDL_Rect tile = {tileType%16 * TILE_SIZE, tileType/16 * TILE_SIZE, TILE_SIZE, TILE_SIZE};
			box.x = box.x - camera.x;
			box.y = box.y - camera.y - m_tiles[i].getHeight();
			SDL_RenderCopy(m_renderer, m_tileSet, &tile, &box);
		}
		else
		{
			m_tiles[i].setVisible(false);
			m_tiles[i].changeHeight(-20);
			if(m_tiles[i].getHeight() > -WINDOW_HEIGHT / 2 + 10)
			{
				SDL_Rect tile = {tileType%16 * TILE_SIZE, tileType/16 * TILE_SIZE, TILE_SIZE, TILE_SIZE};
				box.x = box.x - camera.x;
				box.y = box.y - camera.y - m_tiles[i].getHeight();
				SDL_RenderCopy(m_renderer, m_tileSet, &tile, &box);
			}
		}
	}
}

bool Floor::touchesWall(SDL_Rect box)
{
	for(int i(0); i < m_totalTiles; i++)
	{
		if(m_tiles[i].isVisible())
			if(m_tiles[i].getType() == 0)
				if(checkCollision(box, m_tiles[i].getBox()))
					return true;
	}
	return false;
}

bool Floor::checkCollision(SDL_Rect const& a, SDL_Rect const& b)
{
	return SDL_HasIntersection(&a, &b);
}

int Floor::getDistance(SDL_Rect const& a, SDL_Rect const& b)
{
	SDL_Point centerA = {a.x + a.w/2, a.y + a.h/2};
	SDL_Point centerB = {b.x + b.w/2, b.y + b.h/2};
	
	return sqrt((centerA.x-centerB.x)*(centerA.x-centerB.x) + (centerA.y-centerB.y)*(centerA.y-centerB.y));
}

Tile::Tile() :
	m_type(0), m_height(-WINDOW_HEIGHT)
{
	m_box = {0, 0, 32, 32};
}

Tile::Tile(int x, int y, int tileType) :
	m_type(tileType), m_isVisible(false), m_height(-WINDOW_HEIGHT)
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

bool Tile::isVisible()
{
	return m_isVisible;
}

int Tile::getHeight()
{
	return m_height;
}

void Tile::setBox(SDL_Rect& box)
{
	m_box = box;
}

void Tile::setType(int tileType)
{
	m_type = tileType;
}

void Tile::setVisible(bool isVisible)
{
	m_isVisible = isVisible;
}

void Tile::changeHeight(int y)
{
	m_height += y;
	if(m_height > 0)
		m_height = 0;
	if(m_height < -WINDOW_HEIGHT/2)
		m_height = -WINDOW_HEIGHT/2;
}