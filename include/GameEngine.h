#include <iostream>
#include <SDL3/SDL.h>             
#include <SDL3_image/SDL_image.h> 
#include <SDL3_ttf/SDL_ttf.h>  
#include <vector>
#include <algorithm>
#include <functional>  
#include <map>         

#include "Constants.h"
#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Scene.h"  

//Sprites
#include "Sprite.h"
#include "MovingSprite.h"
#include "AnimatedSprite.h"
#include "TextSprite.h"
#include "TextInputField.h"

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine
{
public:
// Konstruktor och destruktor
    GameEngine(std::string title, int width, int height, int targetfps);

    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;

    ~GameEngine();

    // Huvudmetod för att köra spelet
    void run();

    // Initialiserar SDL och skapar fönster och renderer
    bool initialize(std::string title, int width, int height, int targetfps);

    // Hanterar input och uppdateringar
    void input();

    // Uppdateringsmetod som kan överskrivas av subklasser
    virtual void update(double deltaTime);
    
    // Spelspecifik uppdateringsmetod som kan överskrivas
    virtual void gameUpdate(double deltaTime){}
    

    // Hämtar renderern och event kön
    Renderer& getRenderer() {return gameRenderer; }

    // Hämtar event kön
    const std::vector<SDL_Event>& getEvents() const { return eventQueue; }

    // Renderingsmetod
    void render();

    // Stänger ner SDL, rensar upp minne
    void closeSDL();

    // Sprite hantering och kollisioner
    void addSprite(Sprite* sprite);

    // Tar bort sprite från spelet
    void removeSprite(Sprite* sprite);

    bool checkCollision(const Sprite& a, const Sprite& b);
    // Pixel perfekt kollision mellan två sprites

    bool checkPixelPerfectCollision(const Sprite& a, const Sprite& b);
    // Hantera fysik kollision mellan två MovingSprites

    void handlePhysicsCollision(MovingSprite& a, MovingSprite& b);
    // Lägg till scen

    void addScene(Scene* scene);
    // Sätter den aktiva scenen
    void setActiveScene(const std::string& sceneName);

    // Hämtar den aktiva scenen
    Scene* getActiveScene() { return activeScene; }

    // Hämtar en scen efter namn
    Scene* getScene(const std::string& sceneName);

    // Registrera key callback
    void registerKeyCallback(Key key, std::function<void()> callback);

    // Avregistrera key callback
    void unregisterKeyCallback(Key key);
    

    // Medlemsfunktion för att registrera medlemsfunktions callbacks med Templates
    template<typename T>
    void registerKeyCallback(Key key, T* object, void (T::*memberFunc)())
    {
        keyCallbacks[key] = [object, memberFunc]() {
            (object->*memberFunc)();
        };
    }

private: 
    Renderer gameRenderer;   // Renderare för att rita sprites/scener
    Window gameWindow;       // SDL-fönster som motorn använder
    
    std::vector<Sprite*> sprites; // Alla sprites som motorn uppdaterar/ritar
    
    std::vector<Scene*> scenes;   // Registrerade scener
    Scene* activeScene;           // Nuvarande aktiv scen

    int targetFPS;        // Målat antal bildrutor per sekund
    Uint32 frameStart;    // Starttid för aktuell bildruta (ms)
    Uint32 frameTime;     // Tidsåtgång för aktuell bildruta (ms)
    Uint32 frameDelay;    // Fördröjning för att hålla targetFPS (ms)

    Uint64 lastCounter;   // Senaste högupplösta räknarvärde
    double deltaTime;     // Tidsdelta i sekunder per varv

    std::map<Key, std::function<void()>> keyCallbacks; // Kortkommandon -> callback
    void processKeyCallbacks();                         // Kör registrerade callbacks

    std::vector<SDL_Event> eventQueue; // Kö av inkomna SDL-händelser

    bool quit = false;    // Flagga för att avsluta spelloopen
};

#endif