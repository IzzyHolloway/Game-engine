#ifndef TEXTSPRITE_H
#define TEXTSPRITE_H

#include "Sprite.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class TextSprite : public Sprite
{
public:
    // Konstruktor och destruktor
    TextSprite(Renderer &ren, std::string fontPath, int fontSize,
               std::string text, SDL_Color color, float x, float y);

    ~TextSprite();

    // Inge copy constructor eller assignment
    TextSprite(const TextSprite&) = delete;
    TextSprite& operator=(const TextSprite&) = delete;
    
    // Sätter ny text och uppdaterar texturen
    void setText(Renderer &ren, const std::string &newText);
    void setColor(Renderer &ren, SDL_Color newColor);

        
private:
        // SDL TTF font, text och färg
    TTF_Font *font;
    std::string text;
    SDL_Color color;

    void updateTexture(Renderer &ren);
};

#endif