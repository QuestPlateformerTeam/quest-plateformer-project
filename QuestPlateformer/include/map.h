#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class Map : public sf::Drawable, public sf::Transformable
{
    public:
        Map();
        virtual ~Map();
        bool load(const std::string& tileset, sf::Vector2u tileSize,const int* tiles, unsigned int width, unsigned int height, sf::RenderWindow& window);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Vertex* getVertex();
        sf::VertexArray getVertices();
        int getTileNumber(int x, int y);

    protected:

    private:
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
        sf::Vertex* quad;
        int tileNumber;

};

#endif // MAP_H
