#include <iostream>
#include "SDL3/SDL.h"

#ifndef RENDERER_H
#define RENDERER_H

class Sprite;
class Texture;
class Window;
class Renderer{


    public:
    Renderer();

    // Initialiserar renderern med ett fönster
    Renderer(Window& p_gameWindow);

    // inge copy constructor eller assignment
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    

    // Hämtar den inbyggda SDL renderern
    SDL_Renderer* returnNativeRenderer() const;
    
    // Initialiserar renderern med ett fönster
    void initializeRenderer(Window& gameWindow);

    // Sätter aktuell ritfärg (RGBA)
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    // Rensar backbuffer
    void clear();

    // Presenterar backbuffer till skärmen
    void present();

    
    int getWidth() const { return screenWidth; }
    int getHeight() const { return screenHeight; }

    ~Renderer();

    private: 

    SDL_Renderer* p_gameRenderer; // SDL renderer pekare
    
    
    int screenWidth;  // Cache: fönsterbredd
    int screenHeight; // Cache: fönsterhöjd

    

};




#endif 