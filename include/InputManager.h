#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL3/SDL.h>             
#include <SDL3/SDL_main.h>
#include <vector>

// Enum för tangenter och musknappar
enum class Key{

    Left, Right, Up, Down, Space, Enter, Escape, Backspace, Delete,
    A, B, C, D, E, F, G, H, I, J, K, L,
    M, N, O, P, Q, R, S, T, U, V, W, X,
    Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    Tab, Shift, Ctrl, Alt
};

enum class MouseButton{

    Left = 1, Middle = 2, Right = 3
};

class InputManager{

public:

    // Uppdatera aktuell inmatningsstatus 
    static void update();
    // Batch-uppdatera från given event-vektor
    static void update(const std::vector<SDL_Event>& events);

    // Tangentbords hantering
    static bool getKey(Key key);
    static bool getKeyDown(Key key);
    static bool getKeyUp(Key key);

    // Musknappshantering
    static bool getMouseButton(MouseButton button);
    static bool getMouseButtonDown(MouseButton button);
    static bool getMouseButtonUp(MouseButton button);

    // Aktuell musposition
    static int getMouseX();
    static int getMouseY();

    // Flagga för att avsluta programmet (QUIT)
    static bool shouldQuit();

private:

    // Privat konstruktor för att förhindra instansiering
    InputManager() = delete;

    // Tangentstatus: nuvarande och föregående
    static bool currentKeyState[static_cast<int>(Key::Alt) + 1];
    static bool previousKeyState[static_cast<int>(Key::Alt) + 1];

    // Musknappsstatus: nuvarande och föregående
    static bool currentMouseState[4];
    static bool previousMouseState[4];

    // Mappning från egen Key till SDL_Keycode
    static SDL_Keycode keyToSDL_Key(Key key);

    // Senast lästa musposition
    static int mouseX;
    static int mouseY;

    // Intern quit-flagga
    static bool quit;

};

#endif