#ifndef ENGINE_CORE_ENGINE_HPP
#define ENGINE_CORE_ENGINE_HPP

#include "SDL.h"

#include "Engine/Core/Drawable.hpp"
#include "Engine/Core/Updatable.hpp"
#include "Engine/Core/InputHandler.hpp"
#include "Engine/Graphics/Light.hpp"
#include "Engine/Scene/SceneObject.hpp"

#include <vector>

class Camera;

class Engine
{
public:
    Engine(const Engine &other) = delete;
    ~Engine();

    static Engine &getInstance();

    SDL_Window* getWindow()
    {
        return _window;
    }

    Camera* getCamera()
    {
        return _camera;
    }

    SceneObject* getSceneRoot()
    {
        return _sceneRoot;
    }

    const std::vector<Light*> &getLights() const
    {
        return _lights;
    }

    void init(int width, int height);
    void run();

    void addLight(Light* light);
    void removeLight(Light* light);
    
    void addDrawable(Drawable* drawable);
    void removeDrawable(Drawable* drawable);
    void addUpdatable(Updatable* updatable);
    void removeUpdatable(Updatable* updatable);
    void addInputHandler(InputHandler* input);
    void removeInputHandler(InputHandler* input);
    
    Engine &operator =(const Engine &other) = delete;

private:
    Engine();

    void initGL();
    void updateAndDraw(float deltaTime);

    int _width;
    int _height;
    float _totalTime;
    Camera* _camera;
    SDL_Window* _window;
    SDL_GLContext _context;
    SceneObject* _sceneRoot;
    std::vector<Drawable*> _drawables;
    std::vector<Updatable*> _updatables;
    std::vector<InputHandler*> _input;
    std::vector<Light*> _lights;
};

#endif