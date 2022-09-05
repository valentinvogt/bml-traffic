#include <SFML/Graphics.hpp>
#include <vector>
using color = sf::Color;

#ifndef BML_DISPLAY_H
#define BML_DISPLAY_H


class display
{
public:
    std::vector<sf::Vertex> matrix;
    unsigned W;
    unsigned H;
    display(unsigned w, unsigned h);
    void set_pixel(unsigned i, unsigned j, color col);
};


#endif //BML_DISPLAY_H
