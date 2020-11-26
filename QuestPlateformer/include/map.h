#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Map : public sf::Drawable, public sf::Transformable
{
    public:
        Map();
        virtual ~Map();
        bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, sf::RenderWindow& window);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:

    private:
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

};

#endif // MAP_H
