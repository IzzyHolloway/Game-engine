#include "Scene.h"
#include "Renderer.h"
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <iostream>

Scene::Scene(const std::string& name)
    : sceneName(name), backgroundPath(""), backgroundTexture(nullptr) 
{
    // Skapa tom scen med namn; ingen bakgrund från start
}

Scene::~Scene()
{
    // Frigör allokerade sprites
    for(auto sprite : sprites)
    {
        delete sprite;
    }
    sprites.clear();

    // Frigör bakgrundstextur om satt
    if (backgroundTexture)
    {
        SDL_DestroyTexture(backgroundTexture);
    }

}

void Scene::addSprite(Sprite* sprite)
{
    // Lägg till sprite i scenens lista
    sprites.push_back(sprite);
}

void Scene::removeSprite(Sprite* sprite)
{
    // Ta bort första förekomsten av sprite
    auto it = std::find(sprites.begin(), sprites.end(), sprite);
    if (it != sprites.end())
    {
        sprites.erase(it);
    }
}

void Scene::update(float deltaTime)
{
    // Uppdatera alla sprites i scenen
    for (auto sprite : sprites)
    {
        sprite->tick(deltaTime);
    }
}

void Scene::render(Renderer& ren)
{
    // Rita bakgrund över hela fönstret om den finns
    if (backgroundTexture)
    {
        SDL_FRect destRect = {
            0, 
            0, 
            static_cast<float>(ren.getWidth()), 
            static_cast<float>(ren.getHeight())
        };
        SDL_RenderTexture(ren.returnNativeRenderer(), backgroundTexture, nullptr, &destRect);
    }
    
    // Rita alla sprites i scenen
    for (auto sprite : sprites)
    {
        sprite->render(ren);
    }
}

void Scene::setBackground(const std::string& backgroundPath, Renderer& ren)
{
    this->backgroundPath = backgroundPath;
    
    // Frigör gammal bakgrund om den fanns
    if (backgroundTexture)
    {
        SDL_DestroyTexture(backgroundTexture);
    }
    
    // Ladda ny bakgrundstextur
    backgroundTexture = IMG_LoadTexture(ren.returnNativeRenderer(), backgroundPath.c_str());
    
    if (!backgroundTexture)
    {
        std::cout << "Misslyckades ladda bakgrund: " << backgroundPath << std::endl;
    }
}