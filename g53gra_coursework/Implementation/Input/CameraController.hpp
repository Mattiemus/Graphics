#ifndef IMPLEMENTATION_INPUT_CAMERACONTROLLER_HPP
#define IMPLEMENTATION_INPUT_CAMERACONTROLLER_HPP

#include "Engine/Core/InputHandler.hpp"
#include "Engine/Core/Updatable.hpp"
#include "Engine/Math/Vector3.hpp"

class CameraController : public InputHandler, public Updatable
{
public:
    CameraController();
    CameraController(const CameraController &other) = delete;
    virtual ~CameraController();

    virtual void keyDown(SDL_Keycode key);
    virtual void keyUp(SDL_Keycode key);
    virtual void mouseMoved(int newX, int newY);

    virtual void update(float deltaTime, float totalTime);

    CameraController &operator =(const CameraController &other) = delete;

private:
    bool _leftDown;
    bool _rightDown;
    bool _upDown;
    bool _downDown;
    int _mouseX;
    int _mouseY;
    Vector3 _xAxis;
    Vector3 _yAxis;
    Vector3 _zAxis;
};

#endif