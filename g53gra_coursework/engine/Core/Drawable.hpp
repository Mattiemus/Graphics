#ifndef ENGINE_CORE_DRAWABLE_HPP
#define ENGINE_CORE_DRAWABLE_HPP

class Drawable
{
public:
    Drawable();
    Drawable(const Drawable &other) = delete;
    virtual ~Drawable();

    virtual void draw(float deltaTime, float totalTime);

    Drawable &operator =(const Drawable &other) = delete;
};

#endif