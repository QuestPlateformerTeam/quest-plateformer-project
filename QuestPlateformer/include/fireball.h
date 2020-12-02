#ifndef FIREBALL_H
#define FIREBALL_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Fireball : public sf::Drawable
{
    public:
        Fireball();
        virtual ~Fireball();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:

    private:
        sf::RectangleShape fireball;
        int positionX;
        int positionY;
};

#endif // FIREBALL_H
