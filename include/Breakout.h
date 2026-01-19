#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "GameEngine.h"

class Breakout : public GameEngine
{
public:
    // Konstruktor och destruktor
    Breakout(std::string title, int width, int height, int targetfps);
    ~Breakout();
    
    // Inge copy constructor eller assignment
    Breakout(const Breakout&) = delete;
    Breakout& operator=(const Breakout&) = delete;

    // Spelspecifik uppdateringsmetod
    void gameUpdate(double deltaTime) override;
    // Uppdateringsmetod som hanterar input och speluppdateringar
    void update(double deltaTime) override;
    
private:
    // Spelspecifika metoder
    void initGame();
    // Hanterar kollisioner mellan bollen och väggar, paddle och bricko
    void handleCollisions();
    // Kollar kollisioner mellan bollen och brickor
    void checkBrickCollisions();
    // Återställer bollens position och hastighet
    void resetBall();
    
    MovingSprite* paddle;            // Spelarens racket
    MovingSprite* ball;              // Bollen
    std::vector<Sprite*> bricks;     // Tegelstenar att slå sönder
    TextSprite* livesText;           // HUD: livtext
    
    int lives;       // Antal liv kvar
    int score;       // Poäng
    bool ballLaunched; // Om bollen är skickad
    
    // Konstanta värden för spelet detta är för spelet så vill inte ha de i Constants.h
    static constexpr float PADDLE_SPEED = 400.0f;
    static constexpr float BALL_SPEED = 300.0f;
    static constexpr int BRICK_ROWS = 5;
    static constexpr int BRICK_COLS = 10;
    static constexpr int BRICK_WIDTH = 60;
    static constexpr int BRICK_HEIGHT = 20;
    static constexpr int BRICK_PADDING = 5;
};

#endif
