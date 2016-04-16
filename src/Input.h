#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#define JOY0 0
#define JOY1 1
#define JOY2 2
#define JOY3 3

// SDL2
#include "common.h"

class Input
{
public:
    Input();
    ~Input();
    void updateEvents();
    bool terminate() const;

    // Keyboard & mouse
    bool getKey(const SDL_Scancode key) const;
    bool getMouseButton(const Uint8 button) const;
    bool mouseMotion() const;
    int getMouseX() const;
    int getMouseY() const;
    int getMouseRelX() const;
    int getMouseRelY() const;

    // GameControllers
    void openGameControllers();
    void closeGameControllers();
    void autoMap();
    bool getControllerButton(const int gameControllerNumber, const Uint8 button) const;
    int getControllerAxes(const int gameControllerNumber, const Uint8 axis) const;
    Uint8 getControllerHat(const int gameControllerNumber) const;

    // Pointer
    void afficherPtr(bool response) const;
    void capturePtr(bool response) const;

private:
    SDL_Event m_events;

    // Keyboard & mouse
    bool m_keys[SDL_NUM_SCANCODES];
    bool m_mouseButtons[8];

    int m_mouseX;
    int m_mouseY;
    int m_mouseRelX;
    int m_mouseRelY;

    // GameControllers
    int m_numGameControllers;
    SDL_GameController* m_gameControllers[4];

    bool m_gameControllerButtons[4][13];  // Max 13 buttons
    Sint16 m_gameControllerAxes[4][6];    // Max 6 axes
    Uint8 m_gameControllerHat[4];

    // Close
    bool m_terminate;
};

#endif // INPUT_H_INCLUDED
