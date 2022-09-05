#include "states.h"

states::states(unsigned w, unsigned h) :
        colors(h, std::vector<unsigned>(w, 0)),
        W(w),
        H(h)
{}

unsigned states::get_color(unsigned i, unsigned j) const
{
    i = i % H;
    j = j % W;
    return colors[i][j];
}

void states::set_color(unsigned i, unsigned j, unsigned col)
{
    i = i % H;
    j = j % W;
    colors[i][j] = col;
}

bool states::check_x(unsigned n, unsigned i, unsigned j, unsigned col) const
{
    for (unsigned k = i + 1; k <= i + n; ++k)
    {
        if (get_color(k, j) != col)
            return false;
    }
    return true;
}

bool states::check_y(unsigned n, unsigned i, unsigned j, unsigned col) const
{
    for (unsigned k = j + 1; k <= j + n; ++k)
    {
        if (get_color(i, k) != col)
            return false;
    }
    return true;
}