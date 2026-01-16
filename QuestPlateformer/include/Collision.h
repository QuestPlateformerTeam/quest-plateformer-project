#ifndef COLLISION_H
#define COLLISION_H

namespace Collision {
    bool PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);
}

#endif
