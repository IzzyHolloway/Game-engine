#include <SDL3/SDL.h>
#include <iostream>

#ifndef WINDOW_H
#define WINDOW_H


class Renderer;
class Window{

    public:
    // Konstruktorer
    Window();
    Window(std::string title, const int width, const int height);

    // inge copy constructor eller assignment 
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Initialiserar SDL fönstret
    SDL_Window* initializeWindow(const std::string title, const int width, const int height);
    // Hämta SDL_Window*
    SDL_Window* returnNativeWindow() const;


    ~Window();
    
    private:
    
    // Pekare till SDL fönstret
    SDL_Window* p_gameWindow;
    
    // Intern uppdatering av titel/storlek
    void updateWindow();


    
};

#endif