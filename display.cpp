#include "display.h"
#include <SFML/Graphics.hpp>

display::display(unsigned w, unsigned h) :
        matrix(w * h),
        W(w),
        H(h)
{}

void display::set_pixel(unsigned i, unsigned j, color col) {
    i = i % H;
    j = j % W;
    matrix[(i * W) + j] = sf::Vertex(sf::Vector2f(j, i), col);
}