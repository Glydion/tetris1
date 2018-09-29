#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "SDL.h"
#include "SDL_image.h"

class Entity
{
    public:
        Entity(SDL_Renderer* renderer);
        virtual ~Entity();

        float x, y, width, height;

        virtual void Update(float delta);
        virtual void Render(float delta);

        bool Collides(Entity* other);

    protected:
        SDL_Renderer* renderer;
};


#endif // ENTITY_H_INCLUDED
