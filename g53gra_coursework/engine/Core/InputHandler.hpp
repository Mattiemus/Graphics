#ifndef ENGINE_CORE_INPUTHANDLER_HPP
#define ENGINE_CORE_INPUTHANDLER_HPP

#include "SDL.h"

class InputHandler
{
public:
    InputHandler();
    InputHandler(const InputHandler &other) = delete;
    virtual ~InputHandler();

    virtual void keyDown(SDL_Keycode key);
    virtual void keyUp(SDL_Keycode key);
    virtual void mouseButtonDown(int button);
    virtual void mouseButtonUp(int button);
    virtual void mouseWheel(int newX, int newY);
    virtual void mouseMoved(int newX, int newY);
    
    InputHandler &operator =(const InputHandler &other) = delete;
};

#endif