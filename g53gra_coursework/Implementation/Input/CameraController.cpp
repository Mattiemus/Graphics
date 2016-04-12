#include "Implementation/Input/CameraController.hpp"
#include "Engine/Graphics/Camera.hpp"
#include "Engine/Core/Engine.hpp"

#include <cmath>
#include <iostream>

using namespace std;

CameraController::CameraController()
    : _leftDown(false), _rightDown(false), _upDown(false), _downDown(false), 
    _mouseX(0), _mouseY(0),
    _xAxis(Engine::getInstance().getCamera()->getRight()), _yAxis(Engine::getInstance().getCamera()->getUp()), _zAxis(Engine::getInstance().getCamera()->getDirection())
{
}

CameraController::~CameraController()
{
}

void CameraController::keyDown(SDL_Keycode key)
{
    if (key == SDLK_LEFT || key == SDLK_a) {
        _leftDown = true;
    }
    if (key == SDLK_RIGHT || key == SDLK_d) {
        _rightDown = true;
    }
    if (key == SDLK_UP || key == SDLK_w) {
        _upDown = true;
    }
    if (key == SDLK_DOWN || key == SDLK_s) {
        _downDown = true;
    }
}

void CameraController::keyUp(SDL_Keycode key)
{
    if (key == SDLK_LEFT || key == SDLK_a) {
        _leftDown = false;
    }
    if (key == SDLK_RIGHT || key == SDLK_d) {
        _rightDown = false;
    }
    if (key == SDLK_UP || key == SDLK_w) {
        _upDown = false;
    }
    if (key == SDLK_DOWN || key == SDLK_s) {
        _downDown = false;
    }
}

void CameraController::mouseMoved(int newX, int newY)
{
    _mouseX = newX;
    _mouseY = newY;
}

void CameraController::update(float deltaTime, float totalTime)
{
    // Rotation
    int centerX = 1024 / 2;
    int centerY = 768 / 2;
    int dx = centerX - _mouseX;
    int dy = centerY - _mouseY;
    Quaternion finalRotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    if (dx != 0) {
        float deltaAngle = deltaTime * 0.1f * static_cast<float>(dx);
       finalRotation = Quaternion::fromAngleAxis(deltaAngle, Vector3(0.0f, 1.0f, 0.0f));
    }
    if (dy != 0) {
        Quaternion pitchRot;
        float deltaAngle = deltaTime * 0.1f * static_cast<float>(dy);
        finalRotation = finalRotation * Quaternion::fromAngleAxis(deltaAngle, _xAxis);
    }
    _xAxis.transform(finalRotation); 
    _xAxis.normalize();
    _yAxis.transform(finalRotation); 
    _yAxis.normalize();
    _zAxis.transform(finalRotation); 
    _zAxis.normalize();
    Engine::getInstance().getCamera()->setRight(_xAxis);
    Engine::getInstance().getCamera()->setUp(_yAxis);
    Engine::getInstance().getCamera()->setDirection(_zAxis);
    Engine::getInstance().getCamera()->recompute();

    // Movement
    Vector3 movementDirection;
    if (_leftDown) {
       movementDirection = movementDirection - _xAxis;
    }
    if (_rightDown) {
        movementDirection = movementDirection + _xAxis;
    }
    if (_upDown) {
        movementDirection = movementDirection + _zAxis;
    }
    if (_downDown) {
        movementDirection = movementDirection - _zAxis;
    }
    Vector3 newPosition = Engine::getInstance().getCamera()->getPosition() + (movementDirection * deltaTime * 5000.0f);
    Engine::getInstance().getCamera()->setPosition(newPosition);

    // Reset the mouse
    SDL_WarpMouseInWindow(Engine::getInstance().getWindow(), centerX, centerY);
}
