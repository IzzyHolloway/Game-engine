#include "TextSprite.h"
#include "Renderer.h"
#include <iostream>

TextSprite::TextSprite(Renderer &ren, std::string fontPath, int fontSize,
                       std::string text, SDL_Color color, float x, float y)
    : Sprite()
{

    // Initiera position för text-sprite
    this->xPosition = x;
    this->yPosition = y;

    this->sourceRect = nullptr;
    this->p_sprite = nullptr;

    this->text = text;
    this->color = color;

    // Öppna TTF-font
    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    if (!font)
    {
        SDL_Log("Kunde inte ladda font '%s': %s", fontPath.c_str(), SDL_GetError());
    }

    // Skapa initial textur för texten
    updateTexture(ren);
}

TextSprite::~TextSprite()
{
    // Stäng font om öppnad
    if (font)
    {
        TTF_CloseFont(font);
    }
}

void TextSprite::setText(Renderer &ren, const std::string &newText)
{
    if (text != newText)
    {
        // Uppdatera text och bygg ny textur
        text = newText;
        updateTexture(ren);
    }
}

void TextSprite::setColor(Renderer &ren, SDL_Color newColor)
{
    if (color.r != newColor.r || color.g != newColor.g || color.b != newColor.b || color.a != newColor.a)
    {
        // Byt färg och uppdatera textur
        color = newColor;
        updateTexture(ren);
    }
}

void TextSprite::updateTexture(Renderer &ren)
{
    if (!font)
        return;

    // Frigör tidigare textur om den finns
    if (this->p_sprite)
    {
        SDL_DestroyTexture(this->p_sprite);
        this->p_sprite = nullptr;
    }

    if (text.empty())
        return;

    // Rendera text till surface och skapa texture
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), 0, color);

    if (surface)
    {
        this->p_sprite = SDL_CreateTextureFromSurface(ren.returnNativeRenderer(), surface);

        // Uppdatera storlek baserat på renderad text
        this->width = static_cast<float>(surface->w);
        this->height = static_cast<float>(surface->h);

        SDL_DestroySurface(surface);
    }
    else
    {
        SDL_Log("Kunde inte rendera text: %s", SDL_GetError());
    }
}