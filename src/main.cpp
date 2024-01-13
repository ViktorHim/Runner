#include "Game.h"

int WinMain() {
    Vector2D resolution = Vector2D(800, 600);
    Game game = Game(resolution);
    game.start();
    return 0;
}