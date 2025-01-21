#include "../Header Files/Collision.h"


bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
        )
        return true;
    else
        return false;
    
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    if (AABB(colA.collider, colB.collider))
    {
        std::cout << colA.tag << "hit " << colB.tag << '\n';
        return true;
    }
    else
        return false;
}
