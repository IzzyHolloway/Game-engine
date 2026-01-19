#include "Window.h"
#include <iostream>

Window::Window(std::string title, const int width, const int height)
{
    // Skapa fönster direkt vid konstruktion
    p_gameWindow = initializeWindow(title, width, height);
}

Window::Window()
{
    
}


Window::~Window()
{
    // Stäng och frigör SDL_Window
    SDL_DestroyWindow(p_gameWindow);
}

SDL_Window* Window::initializeWindow(const std::string title, const int width, const int height)
{
    // Skapa fönster; om misslyckas, logga fel
    if(p_gameWindow = SDL_CreateWindow(title.c_str(), width, height, 0); p_gameWindow == nullptr)   
    {         
        SDL_Log("Window could not be created! %s", SDL_GetError());    
        
    }

    return p_gameWindow; 
}




SDL_Window* Window::returnNativeWindow() const
{
    // Ge access till SDL_Window*
    return p_gameWindow;
}

