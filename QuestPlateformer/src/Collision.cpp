#include <SFML/Graphics.hpp>
#include <map>

namespace Collision
{
    // Gère les bitmasks pour le pixel-perfect collision
    class BitmaskManager
    {
    public:
        ~BitmaskManager() {
            for (auto& pair : Bitmasks)
                delete[] pair.second;
        }

        sf::Uint8 GetPixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
            if (x >= tex->getSize().x || y >= tex->getSize().y)
                return 0;
            return mask[x + y * tex->getSize().x];
        }

        sf::Uint8* GetMask(const sf::Texture* tex) {
            auto it = Bitmasks.find(tex);
            if (it == Bitmasks.end()) {
                sf::Image img = tex->copyToImage();
                return CreateMask(tex, img);
            } else {
                return it->second;
            }
        }

        sf::Uint8* CreateMask(const sf::Texture* tex, const sf::Image& img) {
            sf::Uint8* mask = new sf::Uint8[tex->getSize().x * tex->getSize().y];
            for (unsigned int y = 0; y < tex->getSize().y; y++) {
                for (unsigned int x = 0; x < tex->getSize().x; x++)
                    mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
            }
            Bitmasks[tex] = mask;
            return mask;
        }

    private:
        std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
    };

    inline BitmaskManager Bitmasks;

    // Test de collision pixel-perfect entre deux sprites
    bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit) {
        sf::FloatRect Intersection;
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
            sf::IntRect O1SubRect = Object1.getTextureRect();
            sf::IntRect O2SubRect = Object2.getTextureRect();

            sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
            sf::Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());

            for (int i = (int)Intersection.left; i < (int)(Intersection.left + Intersection.width); i++) {
                for (int j = (int)Intersection.top; j < (int)(Intersection.top + Intersection.height); j++) {
                    sf::Vector2f o1v = Object1.getInverseTransform().transformPoint((float)i, (float)j);
                    sf::Vector2f o2v = Object2.getInverseTransform().transformPoint((float)i, (float)j);

                    if (o1v.x >= 0 && o1v.y >= 0 && o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
                        o2v.x >= 0 && o2v.y >= 0 && o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {
                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)o1v.x + O1SubRect.left, (int)o1v.y + O1SubRect.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)o2v.x + O2SubRect.left, (int)o2v.y + O2SubRect.top) > AlphaLimit)
                            return true;
                    }
                }
            }
        }
        return false;
    }
}
