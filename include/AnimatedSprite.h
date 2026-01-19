#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H


#include "MovingSprite.h"
#include <vector>


class AnimatedSprite : public MovingSprite
{
    public:

    // Animerad sprite med spritesheet-parametrar 
    AnimatedSprite(Renderer& ren, std::string path, float w, float h, float x, float y, 
        int frameWidth, int frameHeight, int numFrames, float frameDelay); 


    AnimatedSprite(const AnimatedSprite&) = delete;

    AnimatedSprite& operator=(const AnimatedSprite&) = delete;

    ~AnimatedSprite() override;

    // Uppdatera rörelse och stega animation baserat på frameDelay
    void tick(float deltaTime) override;

    // Starta animation
    void play();

    // Pausa animation
    void pause();

    // Stoppa och nollställ animationen
    void stop();

    // Sätt tidsfördröjning mellan frames 
    void setFrameDelay(float delay);

    private: 
    int currentFrame;   // Aktuellt frame-index
    int numFrames;      // Antal frames i spritesheet
    float frameDelay;   // Tid mellan frames
    float frameTimer;   // Ackumulerad tid sedan senaste frame-byte
    bool isPlaying;     // Om animationen är aktiv

    int frameWidth;     // Bredd per frame i spritesheet
    int frameHeight;    // Höjd per frame i spritesheet

    void updateFrame(); // Beräkna och sätt källrektangel för aktuellt frame

    
};

#endif