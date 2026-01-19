#include "Breakout.h"
#include <cmath>


//Constructor för spelet sätter värderna
Breakout::Breakout(std::string title, int width, int height, int targetfps) 
    : GameEngine(title, width, height, targetfps)
{
    paddle = nullptr;
    ball = nullptr;
    livesText = nullptr;
    lives = 3;
    score = 0;
    ballLaunched = false;
    
    // Initiera pekare och spelstatus
    //Laddar ljud vid konstruktion
    AudioManager::loadSound("ballbounce", constants::ballbounce_str);

    AudioManager::loadSound("destroybrick", constants::destroybrick_str);
    
    initGame();
}


//Destructor tar bort o städar upp Sprites
Breakout::~Breakout()
{
    // Skapa spelobjekt och sceninnehåll
    removeSprite(paddle);
    removeSprite(ball);
    removeSprite(livesText);
    

    // Ta bort alla brickro
    for (size_t i = 0; i < bricks.size(); i++) 
    // Ta bort HUD och spelobjekt ur motorn
    {
        removeSprite(bricks[i]);
    }
}

    // Ta bort alla brickor
// Sätter upp spelet med paddle, boll och tegelstenar
void Breakout::initGame()
{
    //variabler för paddle position och storlek
    float paddleWidth = 100;
    float paddleHeight = 20;


    //paddle position
    float paddleX = constants::gScreenWidth / 2 - paddleWidth / 2;
    float paddleY = constants::gScreenHeight - 50;


    // Dynamiskt skapa paddle och boll
    paddle = new MovingSprite(getRenderer(), constants::paddle_str, paddleWidth, paddleHeight, paddleX, paddleY);
    addSprite(paddle);
    
    float ballSize = 10;
    float ballX = constants::gScreenWidth / 2 - ballSize / 2;
    float ballY = constants::gScreenHeight - 80;

    // Dynamiskt skapa boll
    ball = new MovingSprite(getRenderer(), constants::ball_str, ballSize, ballSize, ballX, ballY);
    addSprite(ball);
    

    // Skapa och visa livstext
    livesText = new TextSprite(getRenderer(), constants::arial_font, 24, "Lives: " + std::to_string(lives), {255, 255, 255, 255}, 10, 10);
    addSprite(livesText);
    
    // Skapa brickor att förstöra
    int totalBricksWidth = BRICK_COLS * (BRICK_WIDTH + BRICK_PADDING);
    int bricksStartX = (constants::gScreenWidth - totalBricksWidth) / 2;
    int bricksStartY = 50;
    

    // Loop för att skapa rader och kolumner av bickor
    for (int row = 0; row < BRICK_ROWS; row++) {
        std::string brickImage;
        
        if (row == 0) {
            brickImage = constants::brick_red_str;
        } else if (row == 1) 
        {
            brickImage = constants::brick_orange_str;
        } else if (row == 2) 
        {
            brickImage = constants::brick_yellow_str;
        } else if (row == 3) 
        {
            brickImage = constants::brick_green_str;
        } else 
        {
            brickImage = constants::brick_blue_str;
        }
        
        for (int col = 0; col < BRICK_COLS; col++) 
        {
            // Beräkna position för varje bricka
            float brickX = bricksStartX + col * (BRICK_WIDTH + BRICK_PADDING);
            float brickY = bricksStartY + row * (BRICK_HEIGHT + BRICK_PADDING);
            
            //dynamiskt skapa bricka
            Sprite* brick = new Sprite(getRenderer(), brickImage, BRICK_WIDTH, BRICK_HEIGHT, brickX, brickY);
            bricks.push_back(brick);
            addSprite(brick);
        }
    }
    

    // Reset balens status
    ballLaunched = false;
}


// Uppdateringsmetod som hanterar input och speluppdateringar
void Breakout::update(double deltaTime)
{
    GameEngine::update(deltaTime);
    

    // Hantera paddle input och bollstart
    bool leftPressed = InputManager::getKey(Key::Left) || InputManager::getKey(Key::A);
    bool rightPressed = InputManager::getKey(Key::Right) || InputManager::getKey(Key::D);
    bool spacePressed = InputManager::getKey(Key::Space);
    

    // Uppdatera paddle rörelse baserat på input
    if (leftPressed) 
    {
        paddle->setXVelocity(-PADDLE_SPEED);
    } else if (rightPressed) 
    {
        paddle->setXVelocity(PADDLE_SPEED);
    } else 
    {
        paddle->setXVelocity(0);
    }
    

    // Begränsa paddle inom skärm
    if (paddle->getX() < 0) 
    {
        paddle->addPosition(-paddle->getX(), 0);
    }
    if (paddle->getX() + paddle->getWidth() > constants::gScreenWidth) 
    {
        float overX = (paddle->getX() + paddle->getWidth()) - constants::gScreenWidth;
        paddle->addPosition(-overX, 0);
    }

    // Launcha bollen om spacebar trycks
    if (spacePressed && !ballLaunched) 
    {

        ballLaunched = true;

        ball->setXVelocity(BALL_SPEED * 0.5f);
        ball->setYVelocity(-BALL_SPEED);

    }
    
    gameUpdate(deltaTime);
}

void Breakout::gameUpdate(double deltaTime)
{
    if (!ballLaunched) 
    {

        // Bollen följer paddlen innan den skjuts
        float ballX = paddle->getX() + paddle->getWidth() / 2 - ball->getWidth() / 2;
        float ballY = paddle->getY() - ball->getHeight() - 10;
        float deltaX = ballX - ball->getX();
        float deltaY = ballY - ball->getY();

        ball->addPosition(deltaX, deltaY);
    }
    
    handleCollisions();
}
// Hanterar kollisioner mellan bollen och väggar, paddle och bricko
void Breakout::handleCollisions()
{
    // Kollision med väggar
    if (ball->getX() <= 0 && ball->getXVelocity() < 0) 
    {


        ball->addPosition(-ball->getX(), 0); 
        ball->setXVelocity(-ball->getXVelocity());
        AudioManager::playSound("ballbounce");
    } 
    // Höger vägg
    if (ball->getX() + ball->getWidth() >= constants::gScreenWidth && ball->getXVelocity() > 0) 
    {
        float overlapX = (ball->getX() + ball->getWidth()) - constants::gScreenWidth;
        ball->addPosition(-overlapX, 0); 
        ball->setXVelocity(-ball->getXVelocity());
        AudioManager::playSound("ballbounce");
    }
    // Topp vägg
    if (ball->getY() <= 0 && ball->getYVelocity() < 0)
    {
        ball->addPosition(0, -ball->getY()); 
        ball->setYVelocity(-ball->getYVelocity());
        AudioManager::playSound("ballbounce");
    }
    // Botten vägg
    if (ball->getY() >= constants::gScreenHeight)
    {
        lives--;
        livesText->setText(getRenderer(), "Lives: " + std::to_string(lives));
        resetBall();
        
        if (lives <= 0) 
        {
            lives = 3;
            score = 0;
            initGame();
        }
    }
    

    // Kollision med paddle
    bool ballMovingDown = ball->getYVelocity() > 0;
    if (checkCollision(*ball, *paddle) && ballMovingDown)
    {
        AudioManager::playSound("ballbounce");
        
        float ballCenterX = ball->getX() + ball->getWidth() / 2;
        float paddleCenterX = paddle->getX() + paddle->getWidth() / 2;
        float hitPosition = (ballCenterX - paddleCenterX) / (paddle->getWidth() / 2);
        
        ball->setXVelocity(BALL_SPEED * hitPosition);
        ball->setYVelocity(-BALL_SPEED);
        
        float desiredY = paddle->getY() - ball->getHeight();
        float deltaY = desiredY - ball->getY();
        ball->addPosition(0, deltaY);
        
        float minSpeed = 50.0f;


        if (std::abs(ball->getXVelocity()) < minSpeed) 
        {
            if (hitPosition >= 0) 
            {
                ball->setXVelocity(minSpeed);
            } else 
            {
                ball->setXVelocity(-minSpeed);
            }
        }
    }
    
    checkBrickCollisions();
}

// Kollar kollisioner mellan bollen och brickor
void Breakout::checkBrickCollisions()
{
    for (size_t i = 0; i < bricks.size(); i++) 
    {
        if (checkCollision(*ball, *bricks[i])) 
        {
            AudioManager::playSound("destroybrick");
            
            removeSprite(bricks[i]);
            bricks.erase(bricks.begin() + i);
            
            ball->setYVelocity(-ball->getYVelocity());
            score += 10;
            
            if (bricks.size() == 0) 
            {
                resetBall();
                initGame();
            }
            
            break;
        }
    }
}

// Resettar bollens position och hastighet
void Breakout::resetBall()
{
    ballLaunched = false;
    ball->setXVelocity(0);
    ball->setYVelocity(0);
    
    float ballX = paddle->getX() + paddle->getWidth() / 2 - ball->getWidth() / 2;
    float ballY = paddle->getY() - ball->getHeight() - 10;
    float deltaX = ballX - ball->getX();
    float deltaY = ballY - ball->getY();
    
    ball->addPosition(deltaX, deltaY);
}
