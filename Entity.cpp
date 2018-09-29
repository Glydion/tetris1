
#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer)
{
    this->renderer = renderer;

    x = 0;
    y = 0;
    width = 1;
    height = 1;
}

Entity::~Entity()
{

}

void Entity::Update(float delta)
{

}

void Entity::Render(float delta)
{

}

bool Entity::Collides(Entity* other)
{
    // Checks to see if an entity has collided with another

    if( x + width > other->x                // left side
        && x < other->x + other->width      // right side
        && y + height > other->y            // top side
        && y < other->y + other->height )   // bottom side
    {
        return true;
    }

    return false;
}
