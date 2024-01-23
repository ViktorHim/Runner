#include "Tilemap.h"

bool Tilemap::isEmpty(int row, int col)
{
    return map[row][col].isEmpty();
}

void Tilemap::initTileSet()
{
    SDL_Surface* surface = IMG_Load(TILE_SET_PATH);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    tileset[0] = {0,0, 0, 0};
    tileset[1] = {0,0, 16, 16};
    tileset[2] = {16,0, 16, 16};
    tileset[3] = {32,0, 16, 16};
    tileset[4] = {48,0, 16, 16};
    tileset[5] = {64,0, 16, 16};
    tileset[6] = {80,0, 16, 16};
    tileset[7] = {96,0, 16, 16};
    tileset[8] = {0,16, 16, 16};
    tileset[9] = {16,16, 16, 16};
    tileset[10] = {32,16, 16, 16};
    tileset[11] = {0,32, 16, 16};//15
    tileset[12] = {16,32, 16, 16};//16
    tileset[13] = {32,32, 16, 16};//17

}

void Tilemap::render(int x, int y)
{
    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            map[i][j].render(x,y);
        }
    }
}

Vector2D Tilemap::getSize()
{
    return size;
}

Tilemap::Tilemap(SDL_Renderer * renderer, std::string filename)
{
    this->renderer = renderer;
    this->filename = filename;
    std::ifstream inputFile(filename);
    inputFile >> size.y;
    inputFile >> size.x;
    std::cout << size.y << " " << size.x << std::endl;

    map = new Tile*[size.y];

    for(int i = 0; i < size.y; i++)
    {
        map[i] = new Tile[size.x];
    }


    initTileSet();

    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            int tileType;
            inputFile >> tileType;
            map[i][j] = Tile(renderer, {TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE, TILE_SIZE}, tileset[tileType], texture);
        }
    }
    inputFile.close();
}
