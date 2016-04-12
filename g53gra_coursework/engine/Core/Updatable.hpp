#ifndef ENGINE_CORE_UPDATABLE_HPP
#define ENGINE_CORE_UPDATABLE_HPP

class Updatable
{
public:
    Updatable();
    Updatable(const Updatable &other) = delete;
    virtual ~Updatable();

    virtual void update(float deltaTime, float totalTime);

    Updatable &operator =(const Updatable &other) = delete;
};

#endif