#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
#include <fstream>
#define TILE_SET_PATH "sprites/tileset/tiles.png"
#define TILE_SIZE 80
class Tilemap
{
private:
    SDL_Texture * texture;
    SDL_Rect tileset[14];
    Tile ** map;
    Vector2D size;
    std::string filename;
    SDL_Renderer * renderer;
public:
    bool isEmpty(int row, int col);
    void initTileSet();
    void render(int x, int y);
    Vector2D getSize();
    Tilemap(SDL_Renderer * renderer, std::string filename = "levels/Level1.txt");
    ~Tilemap();
};
#endif