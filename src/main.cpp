#include "Game.h"
#include "ScreenSize.h"

int WinMain() {
    Vector2D resolution = Vector2D(WIDTH, HEIGHT);
    Game game = Game(resolution);
    game.start();
    return 0;
}