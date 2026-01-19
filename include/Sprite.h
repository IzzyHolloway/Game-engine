#include <iostream>
#include <SDL3/SDL.h>


#ifndef SPRITE_H
#define SPRITE_H

class Renderer;

class Sprite
{
    public:

    // Standardkonstruktor
    Sprite();

    // Konstruktor utan position, Ingen spritesheet
    Sprite(Renderer& ren, std::string path, float width, float height);

    // Konstruktor med position, Ingen spritesheet
    Sprite(Renderer& ren, std::string path, float width, 
        float height, float xPosition, float yPosition);

    // Spritesheet: srcX/srcY = startposition från övre vänstra hörnet
    // srcW/srcH = utklippsarea 
    Sprite(Renderer& ren, std::string path, float w, float h, float x, float y, float srcX, float srcY, float srcW, float srcH);

    // Destruktor
    virtual ~Sprite();

    // Förbjud värdesemantik (ingen kopiering)
    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;
    
    // Rendera sprite
    virtual void render(Renderer& ren);

    // Ladda sprite efter konstruktion, utan spritesheet
    void load(Renderer& ren, std::string path, float x, float y, float width, float height);

    // Uppdatera per bildruta 
    virtual void tick(float deltaTime);
    
    // Sätt källrektangel (spritesheet utklipp)
    void setSourceRect(float x, float y, float w, float h);

    void setSourceRect(const SDL_FRect& rect);

    // Hämta underliggande SDL-textur
    SDL_Texture* returnNativeSprite() const;

    // Hämta position och storlek
    float getX();

    float getY();

    float getWidth();

    float getHeight();

    // Bounding-rect för enkel kollisionskontroll
    SDL_FRect getBoundingRect() const;
    
    // Flytta sprite med delta
    void addPosition(float dx, float dy);

    private:

    

    protected: 
    float width, height;    // Storlek i pixlar
    float xPosition, yPosition; // Position på skärmen
    SDL_FRect* sourceRect;  // Källrektangel för spritesheet 
    SDL_Texture* p_sprite;  // SDL-textur som representerar spritebilden
    
};



#endif