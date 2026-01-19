#include "Renderer.h"
#include "Window.h"
#include "Sprite.h"


Renderer::Renderer(Window& p_gameWindow)
    : screenWidth(0), screenHeight(0)
{
    // Skapa SDL_Renderer kopplad till fönstret
    p_gameRenderer = SDL_CreateRenderer(p_gameWindow.returnNativeWindow(), NULL);

    if(!p_gameRenderer){
        std::cerr << "Error failed to initialize renderer: " << SDL_GetError() << std::endl;
    }
    
    // Hämta fönsterstorlek för caching
    SDL_GetWindowSize(p_gameWindow.returnNativeWindow(), &screenWidth, &screenHeight);
}

Renderer::Renderer()
    : p_gameRenderer(nullptr), screenWidth(0), screenHeight(0)
{

}

void Renderer::initializeRenderer(Window& gameWindow)
{
    // Initiera renderer i efterhand (om fönster skapas senare)
    p_gameRenderer = SDL_CreateRenderer(gameWindow.returnNativeWindow(), NULL);

    if(!p_gameRenderer){
        std::cerr << "Error failed to initialize renderer: " << SDL_GetError() << std::endl;
    }
    
    
    // Uppdatera cached skärmstorlek
    SDL_GetWindowSize(gameWindow.returnNativeWindow(), &screenWidth, &screenHeight);
}

SDL_Renderer* Renderer::returnNativeRenderer() const
{
    return p_gameRenderer;  
}

Renderer::~Renderer(){
    // Frigör renderer-resurser
    SDL_DestroyRenderer(p_gameRenderer);
}   


void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Sätt ritfärg för efterföljande draw-anrop
    SDL_SetRenderDrawColor(p_gameRenderer, r, g, b, a);
}


void Renderer::clear()
{
    // Rensa backbuffer med aktuell ritfärg
    SDL_RenderClear(p_gameRenderer);
}

void Renderer::present()
{
    // Presentera backbuffer till skärmen
    SDL_RenderPresent(p_gameRenderer);
}



