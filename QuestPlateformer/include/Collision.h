#ifndef COLLISION_H
#define COLLISION_H

namespace Collision {

    // Test pour une collision entre 2 sprites en comparant les valeurs alpha des pixels
    // Supporte les rotations et les mouvements des sprites
    // AlphaLimit: Le seuil auquel un pixel devient "solide".
    // Si AlphaLimit vaut 127, un pixel avec une valeur alpha 128 va provoquer une collision alors qu'un pixel avec une valeur alpha de 126 ne le fera pas.
    //La fonction crée des bitmasks des textures des 2 sprites en téléchargeant les textures de la carte graphique à la mémoire. => Ralenti le pc

    bool PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);

}

#endif	/* COLLISION_H */
