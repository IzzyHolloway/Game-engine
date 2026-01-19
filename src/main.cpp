#include <iostream>
#include "Breakout.h"


int main()
{
    // Skapa spelet (titel, fönsterstorlek, mål-FPS)
    Breakout newGame("Breakout", constants::gScreenWidth, constants::gScreenHeight, 60);
    // Kör spelloopen
    newGame.run();
    
    return 0;
}