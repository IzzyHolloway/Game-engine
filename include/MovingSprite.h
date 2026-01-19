#ifndef MOVINGSPRITE_H
#define MOVINGSPRITE_H

#include "Sprite.h"

class MovingSprite : public Sprite 
{
    public:
    // Konstruktorer och destruktor
    MovingSprite(Renderer& ren, std::string path, float w, float h, float x, 
    float y, float srcX, float srcY, float srcW, float srcH);

    MovingSprite(Renderer& ren, std::string path, float width, float height);

    MovingSprite(Renderer& ren, std::string path, float width, 
        float height, float xPosition, float yPosition);

    ~MovingSprite() override;

    // Inge copy constructor eller assignment
    MovingSprite(const MovingSprite&) = delete;
    MovingSprite& operator=(const MovingSprite&) = delete;
    
    void render(Renderer& ren) override;

    void tick(float deltaTime) override;
    
    // Byt hastighet direkt 
    void changeVelocity(float xValue, float yValue);

    // Hastighet getters/setters
    float getXVelocity();

    float getYVelocity();
    
    void setXVelocity(float value);
    
    void setYVelocity(float value);
    
    void addXVelocity(float value);
    
    void addYVelocity(float value);
    
    void addVelocity(float xValue, float yValue);

    void subtractXVelocity(float value);
    
    void subtractYVelocity(float value);
    
    void subtractVelocity(float xValue, float yValue);
    

    // Fysik metoder
    void setGravity(float gravity);
    float getGravity() const { return gravityForce; }
    
    //elasticitet för studs
    void setElasticity(float elasticity);
    float getElasticity() const { return elasticity; }
    
    //massa för fysik beräkningar
    void setMass(float mass);
    float getMass() const { return mass; }
    
    // Aktivera eller inaktivera fysik
    void applyPhysics(bool enable) { physicsEnabled = enable; }
    bool hasPhysics() const { return physicsEnabled; }

    private:
    float xVelocity, yVelocity; // Hastighet i pixlar per sekund
    
    float gravityForce;        // Gravitationens styrka
    float elasticity;          
    float mass;                // Vikt för fysik
    bool physicsEnabled;       // Om fysik ska tillämpas

};


#endif