#include "Game.h"
#include "ScreenSize.h"
#include <cstdlib>
#include <ctime>

int WinMain() {
    std::srand(std::time(nullptr));
    Vector2D resolution = Vector2D(WIDTH, HEIGHT);
    Game game = Game(resolution);
    game.start();
    return 0;
}