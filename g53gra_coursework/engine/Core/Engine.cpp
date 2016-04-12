#include "Engine/Core/Engine.hpp"
#include "Engine/Core/GL.hpp"
#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Transform.hpp"
#include "Engine/Graphics/Camera.hpp"

#include <iostream>

using namespace std;

Engine::Engine()
    : _width(0), _height(0), _totalTime(0.0f), _camera(nullptr), _window(nullptr), _context(nullptr), _sceneRoot(nullptr)
{
    // Create and add the scene root
    _sceneRoot = new SceneObject();
    addDrawable(_sceneRoot);

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Failed to initialise SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    // Use OpenGL 3.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
}

Engine::~Engine()
{
    // Shutdown
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

Engine &Engine::getInstance()
{
    static Engine instance;
    return instance;
}

void Engine::init(int width, int height)
{
    // Store the viewport size
    _width = width;
    _height = height;
        
    //Create window
    _window = SDL_CreateWindow("G53GRA Graphics Coursework",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        _width, _height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (_window == NULL) {
        cerr << "Couldnt create a window: " << SDL_GetError() << endl;
        exit(1);
    }

    // Create OpenGL context
    _context = SDL_GL_CreateContext(_window);
    if (_context == nullptr) {
        cerr << "Couldnt create OpenGL context: " << SDL_GetError() << endl;
        exit(1);
    }

    // Use Vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        cerr << "Couldnt set VSync " << SDL_GetError() << endl;
        exit(1);
    }

    // Create camera
    _camera = new Camera();
    _camera->setProjection(0.7f, static_cast<float>(width) / static_cast<float>(height), 10.0f, 500000.0f);
    _camera->setPosition(Vector3(-1000.0f, 1000.0f, 1000.0f));
    _camera->lookAt(Vector3(0.0f, 0.0f, -1500.0f), Vector3(0.0f, 1.0f, 0.0f));
    
    initGL();
}

void Engine::initGL()
{
    // Set clear colors
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    // Enable everything we need
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Enable globa client states
    glEnableClientState(GL_VERTEX_ARRAY);

    // Setup depth testing
    glDepthFunc(GL_LEQUAL);

    // Do pretty rendering
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Lambda function to load extensions
    auto loadExtension = [](const char* proc) -> void* {
        void* procAddr = SDL_GL_GetProcAddress(proc);
        if (procAddr == nullptr) {
            cerr << "Failed to load extension: " << proc << endl;
            exit(1);
        }

        return procAddr;
    };

    // Load any required extensions
    // Shaders
    glCreateShader = static_cast<PFNGLCREATESHADERPROC>(loadExtension("glCreateShader"));
    glDeleteShader = static_cast<PFNGLDELETESHADERPROC>(loadExtension("glDeleteShader"));
    glShaderSource = static_cast<PFNGLSHADERSOURCEPROC>(loadExtension("glShaderSource"));
    glCompileShader = static_cast<PFNGLCOMPILESHADERPROC>(loadExtension("glCompileShader"));
    glGetShaderiv = static_cast<PFNGLGETSHADERIVPROC>(loadExtension("glGetShaderiv"));
    glGetShaderInfoLog = static_cast<PFNGLGETSHADERINFOLOGPROC>(loadExtension("glGetShaderInfoLog"));
    glGetProgramInfoLog = static_cast<PFNGLGETPROGRAMINFOLOGPROC>(loadExtension("glGetProgramInfoLog"));
    // Buffers
    glGenBuffers = static_cast<PFNGLGENBUFFERSPROC>(loadExtension("glGenBuffers"));
    glBindBuffer = static_cast<PFNGLBINDBUFFERPROC>(loadExtension("glBindBuffer"));
    glBufferData = static_cast<PFNGLBUFFERDATAPROC>(loadExtension("glBufferData"));
    // Shader programs
    glValidateProgram = static_cast<PFNGLVALIDATEPROGRAMPROC>(loadExtension("glValidateProgram"));
    glCreateProgram = static_cast<PFNGLCREATEPROGRAMPROC>(loadExtension("glCreateProgram"));
    glDeleteProgram = static_cast<PFNGLDELETEPROGRAMPROC>(loadExtension("glDeleteProgram"));
    glAttachShader = static_cast<PFNGLATTACHSHADERPROC>(loadExtension("glAttachShader"));
    glDetachShader​ = static_cast<PFNGLDETACHSHADERPROC>(loadExtension("glDetachShader"));
    glUseProgram = static_cast<PFNGLUSEPROGRAMPROC>(loadExtension("glUseProgram"));
    glLinkProgram = static_cast<PFNGLLINKPROGRAMPROC>(loadExtension("glLinkProgram"));
    // Shader parameters
    glGetUniformLocation = static_cast<PFNGLGETUNIFORMLOCATIONPROC>(loadExtension("glGetUniformLocation"));
    glBindAttribLocation = static_cast<PFNGLBINDATTRIBLOCATIONPROC>(loadExtension("glBindAttribLocation"));
    glProgramUniform1i = static_cast<PFNGLPROGRAMUNIFORM1IPROC>(loadExtension("glProgramUniform1i"));
    glProgramUniform1f = static_cast<PFNGLPROGRAMUNIFORM1FPROC>(loadExtension("glProgramUniform1f"));
    glProgramUniform2f = static_cast<PFNGLPROGRAMUNIFORM2FPROC>(loadExtension("glProgramUniform2f"));
    glProgramUniform3f = static_cast<PFNGLPROGRAMUNIFORM3FPROC>(loadExtension("glProgramUniform3f"));
    glProgramUniform1fv = static_cast<PFNGLPROGRAMUNIFORM1FVPROC>(loadExtension("glProgramUniform1fv"));
    glProgramUniform3fv = static_cast<PFNGLPROGRAMUNIFORM3FVPROC>(loadExtension("glProgramUniform3fv"));
    glProgramUniform4fv = static_cast<PFNGLPROGRAMUNIFORM4FVPROC>(loadExtension("glProgramUniform4fv"));
    glProgramUniformMatrix4fv = static_cast<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>(loadExtension("glProgramUniformMatrix4fv"));
    glGetProgramiv = static_cast<PFNGLGETPROGRAMIVPROC>(loadExtension("glGetProgramiv"));
    glGetActiveUniform = static_cast<PFNGLGETACTIVEUNIFORMPROC>(loadExtension("glGetActiveUniform"));
    // Texture
    glActiveTexture = static_cast<PFNGLACTIVETEXTUREPROC>(loadExtension("glActiveTexture"));
    // Vertex attributes
    glEnableVertexAttribArray = static_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(loadExtension("glEnableVertexAttribArray"));
    glVertexAttribPointer = static_cast<PFNGLVERTEXATTRIBPOINTERPROC>(loadExtension("glVertexAttribPointer"));
    // Frame buffers
    glGenFramebuffers = static_cast<PFNGLGENFRAMEBUFFERSPROC>(loadExtension("glGenFramebuffers"));
    glBindFramebuffer = static_cast<PFNGLBINDFRAMEBUFFERPROC>(loadExtension("glBindFramebuffer"));
    glFramebufferTexture = static_cast<PFNGLFRAMEBUFFERTEXTUREPROC>(loadExtension("glFramebufferTexture"));
    glCheckFramebufferStatus = static_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(loadExtension("glCheckFramebufferStatus"));

    // Setup the viewport
    glViewport(0, 0, _width, _height);
}

void Engine::run()
{
    SDL_Event e;
    int previousTime = SDL_GetTicks();
    bool quit = false;
    while (!quit)  {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) 
            {
                case SDL_QUIT:
                    return;

                case SDL_KEYDOWN:
                    // Quit if esc is pressed
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_Quit();
                        return;
                    } else {
                        for (InputHandler* handler : _input) {
                            handler->keyDown(e.key.keysym.sym);
                        }
                    }
                    break;
                case SDL_KEYUP:
                    for (InputHandler* handler : _input) {
                        handler->keyUp(e.key.keysym.sym);
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    for (InputHandler* handler : _input) {
                        handler->mouseButtonDown(e.button.button);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    for (InputHandler* handler : _input) {
                        handler->mouseButtonUp(e.button.button);
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    for (InputHandler* handler : _input) {
                        handler->mouseWheel(e.wheel.x, e.wheel.y);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    for (InputHandler* handler : _input) {
                        handler->mouseMoved(e.motion.x, e.motion.y);
                    }
                    break;
            }
        }
        
        // Compute the time difference
        int currentTime = SDL_GetTicks();
        int timeDiff = currentTime - previousTime;
        float deltaTime = static_cast<float>(timeDiff) / 1000.0f;
        previousTime = currentTime;

        // Render everything
        updateAndDraw(deltaTime);
        SDL_GL_SwapWindow(_window);
    }
}

void Engine::addLight(Light* light)
{
    _lights.push_back(light);
}

void Engine::removeLight(Light* light)
{
    auto it = find(_lights.begin(), _lights.end(), light);
    if (it != _lights.end()) {
        _lights.erase(it);
    }
}

void Engine::addDrawable(Drawable* drawable)
{
    _drawables.push_back(drawable);
}

void Engine::removeDrawable(Drawable* drawable)
{
    auto it = find(_drawables.begin(), _drawables.end(), drawable);
    if (it != _drawables.end()) {
        _drawables.erase(it);
    }
}

void Engine::addUpdatable(Updatable* updatable)
{
    _updatables.push_back(updatable);
}

void Engine::removeUpdatable(Updatable* updatable)
{
    auto it = find(_updatables.begin(), _updatables.end(), updatable);
    if (it != _updatables.end()) {
        _updatables.erase(it);
    }
}

void Engine::addInputHandler(InputHandler* input)
{
    _input.push_back(input);
}

void Engine::removeInputHandler(InputHandler* input)
{
    auto it = find(_input.begin(), _input.end(), input);
    if (it != _input.end()) {
        _input.erase(it);
    }
}

void Engine::updateAndDraw(float deltaTime)
{
    // Update
    _totalTime += deltaTime;
    for (auto it = _updatables.begin(); it != _updatables.end(); ++it) {
        (*it)->update(deltaTime, _totalTime);
    }

    // Draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto it = _drawables.begin(); it != _drawables.end(); ++it) {
        (*it)->draw(deltaTime, _totalTime);
    }
}