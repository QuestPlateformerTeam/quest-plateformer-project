#include <SFML/Graphics.hpp>
#include <map>
#include "Collision.h"

namespace Collision
{
    //Me permet de cr�e un masque bit de l'image pour v�rifier les valeurs alpha de l'image par la suite
    class BitmaskManager
    {
    public:
        ~BitmaskManager() {
            std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
            for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin(); iter!=end; iter++)
                delete [] iter->second;
        }

        sf::Uint8 GetPixel (const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
            if (x>tex->getSize().x||y>tex->getSize().y)
                return 0;
            return mask[x+y*tex->getSize().x];
        }

        sf::Uint8* GetMask (const sf::Texture* tex) {
            sf::Uint8* mask;
            std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
            if (pair==Bitmasks.end())
            {
                sf::Image img = tex->copyToImage();
                mask = CreateMask (tex, img);
            }
            else
                mask = pair->second;
            return mask;
        }

        sf::Uint8* CreateMask (const sf::Texture* tex, const sf::Image& img) {
            sf::Uint8* mask = new sf::Uint8[tex->getSize().y*tex->getSize().x];
            for (unsigned int y = 0; y<tex->getSize().y; y++)
            {
                for (unsigned int x = 0; x<tex->getSize().x; x++)
                    mask[x+y*tex->getSize().x] = img.getPixel(x,y).a;
            }
            Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex,mask));
            return mask;
        }
    private:
        std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
    };

    BitmaskManager Bitmasks;

    // Test pour une collision entre 2 sprites en comparant les valeurs alpha des pixels
    // Supporte les rotations et les mouvements des sprites
    // AlphaLimit: Le seuil auquel un pixel devient "solide".
    // Si AlphaLimit vaut 127, un pixel avec une valeur alpha 128 va provoquer une collision alors qu'un pixel avec une valeur alpha de 126 ne le fera pas.
    // La fonction cr�e des bitmasks des textures des 2 sprites en t�l�chargeant les textures de la carte graphique � la m�moire. => Ralenti le pc.

    bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit) {
        sf::FloatRect Intersection;
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
            sf::IntRect O1SubRect = Object1.getTextureRect();
            sf::IntRect O2SubRect = Object2.getTextureRect();

            sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
            sf::Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());

            // Loop through our pixels
            for (int i = Intersection.left; i < Intersection.left+Intersection.width; i++) {
                for (int j = Intersection.top; j < Intersection.top+Intersection.height; j++) {

                    sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
                    sf::Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);

                    // Make sure pixels fall within the sprite's subrect
                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
                        o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x)+O1SubRect.left, (int)(o1v.y)+O1SubRect.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x)+O2SubRect.left, (int)(o2v.y)+O2SubRect.top) > AlphaLimit)
                            return true;
                    }
                }
            }
        }
        return false;
    }

}
