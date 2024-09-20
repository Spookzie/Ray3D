#pragma once

#include "Game.h"


int main()
{
    Game game("Ray3D", 1280, 720, 3, 3, true);    


    //  GAME LOOP   //
    while (!game.GetWindowShouldClose())
    {
        game.Update();
        game.Render();        
    }

    return 0;
}