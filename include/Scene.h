#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include "Sprite.h"

class Renderer;

class Scene
{
public:
    Scene(const std::string& name);
    ~Scene();

    // Inge copy constructor eller assignment
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    

    // Hantera sprites i scenen
    void addSprite(Sprite* sprite);
    void removeSprite(Sprite* sprite);
    
    // Uppdaterar alla sprites i scenen
    void update(float deltaTime);
    
    // Rendera scenen
    void render(Renderer& ren);
    

    // Sätter skärmstorlek för scenen
    void setScreenSize(int width, int height);  
    

    // Sätter bakgrundsbild för scenen
    void setBackground(const std::string& backgroundPath, Renderer& ren);
    

    // Hämtar scenens namn
    std::string getName() const { return sceneName; }
    
    // Hämtar alla sprites i scenen
    std::vector<Sprite*>& getSprites() { return sprites; }
    
private:
    std::string sceneName;
    std::vector<Sprite*> sprites;
    std::string backgroundPath;
    SDL_Texture* backgroundTexture; // Bakgrundstextur om satt

    int screenWidth;
    int screenHeight;
};

#endif