//
//  TileMap.hpp
//  ParticlesSim
//
//  Created by Bach Phan on 3/24/18.
//  Copyright © 2018 Bach Phan. All rights reserved.
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include <ResourcePath.hpp>
using namespace sf;

class TileMap : public Drawable
{
public:
    void init(std::string texture_file, unsigned int window_width, unsigned int window_height, unsigned int tile_dimensions)
    {
        m_texture.loadFromFile(texture_file);
        //assert(p_texture != NULL);
        for(int i = 0; i < window_width; i += tile_dimensions)
        {
            for(int j = 0; j < window_height; j += tile_dimensions)
            {
                auto dim = float(tile_dimensions);
                auto grid_tile = RectangleShape(Vector2f(dim,dim));
                grid_tile.move(i, j);
                grid_tile.setTexture(&m_texture);
                auto grid_size = grid_tile.getSize();
                auto texture_size = m_texture.getSize();
                texture_size.x /= 2;
                texture_size.y /= 2;
                grid_tile.setTextureRect(sf::IntRect(grid_size.x, grid_size.y, texture_size.x, texture_size.y));
                grid_tile.setFillColor(sf::Color(255, 255, 255, 128));
                grid_tiles.push_back(grid_tile);
            }
        }
    };
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        for(const auto& tile : grid_tiles){
            target.draw(tile, states);
        }
    };
private:
    Texture m_texture;
    std::vector<RectangleShape> grid_tiles;
};
#endif /* TileMap_hpp */
