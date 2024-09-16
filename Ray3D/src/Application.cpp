#pragma once

#include "Game.h"


int main()
{
    Game game("Ray3D", 640, 480, 4, 5, true);    


    //  GAME LOOP   //
    while (!game.GetWindowShouldClose())
    {
        game.Update();
        game.Render();        
    }

    return 0;
}