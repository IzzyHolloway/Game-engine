#ifndef TEXTINPUTFIELD_H
#define TEXTINPUTFIELD_H

#include "TextSprite.h"
#include <string>

class TextInputField : public TextSprite
{
public:
    // Konstruktor och destruktor
    TextInputField(Renderer& ren, const std::string& fontPath, int fontSize,
                   float x, float y, int maxLength = 20);
    
    TextInputField(const TextInputField&) = delete;
    TextInputField& operator=(const TextInputField&) = delete;
    
    ~TextInputField() override;
    

    // Hanterar textinmatning
    void handleInput(SDL_Event& event);
    

    // Hämtar den aktuella inmatade texten
    std::string getInputText() const { return inputText; }
    void clearInput();
    
    // Aktiverar eller inaktiverar textinmatningsfältet
    void setActive(bool active);
    bool getActive() const { return isActive; }
    
    // Uppdaterings och renderingsmetoder
    void tick(float deltaTime) override;
    void render(Renderer& ren) override;
    
private:
    std::string inputText;
    int maxLength;
    bool isActive;
    bool showCursor;
    float cursorTimer;
    
    void updateDisplayText(Renderer& ren);
};

#endif