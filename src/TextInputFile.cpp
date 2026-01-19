#include "TextInputField.h"
#include "Renderer.h"
#include <iostream>

TextInputField::TextInputField(Renderer& ren, const std::string& fontPath, 
                               int fontSize, float x, float y, int maxLength)
    : TextSprite(ren, fontPath, fontSize, "Name: _", {255, 255, 255, 255}, x, y),
      inputText(""),
      maxLength(maxLength),
      isActive(false),
      showCursor(true),
      cursorTimer(0.0f)
{
    // Initiera inmatningsfält med tom text och blinkande cursor
}

TextInputField::~TextInputField()
{
    // Stoppa textinmatning om fältet är aktivt vid stängning
    if (isActive)
    {
        SDL_Window* window = SDL_GetKeyboardFocus();
        if (window)
        {
            SDL_StopTextInput(window);
        }
    }
}

void TextInputField::setActive(bool active)
{
    isActive = active;
    
    SDL_Window* window = SDL_GetKeyboardFocus();
    if (!window) return;
    
    // Starta/stoppa SDL textinmatning baserat på aktivt tillstånd
    if (isActive)
    {
        SDL_StartTextInput(window);
    }
    else
    {
        SDL_StopTextInput(window);
    }
}

void TextInputField::handleInput(SDL_Event& event)
{
    // Hantera textinmatning och specialtangenter (backspace/enter)
    if (!isActive) return;
    
    if (event.type == SDL_EVENT_TEXT_INPUT)
    {
        if (inputText.length() < static_cast<size_t>(maxLength))
        {
            inputText += event.text.text;
        }
    }
    else if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_BACKSPACE && inputText.length() > 0)
        {
            inputText.pop_back();
        }
        else if (event.key.key == SDLK_RETURN || event.key.key == SDLK_KP_ENTER)
        {
            setActive(false);
        }
    }
}

void TextInputField::tick(float deltaTime)
{
    // Blinka cursor periodiskt 
    cursorTimer += deltaTime;
    if (cursorTimer >= 0.5f)
    {
        showCursor = !showCursor;
        cursorTimer = 0.0f;
    }
}

void TextInputField::clearInput()
{
    // Töm inmatad text
    inputText = "";
}

void TextInputField::render(Renderer& ren)
{
    // Uppdatera visad text innan rendering
    updateDisplayText(ren);
    TextSprite::render(ren);
}

void TextInputField::updateDisplayText(Renderer& ren)
{
    // Bygg visningstext med eventuell cursor
    std::string displayText = "Name: " + inputText;
    
    if (isActive && showCursor)
    {
        displayText += "_";
    }
    
    setText(ren, displayText);
}