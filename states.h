#ifndef BML_STATES_H
#define BML_STATES_H
#include <vector>
using color_matrix = std::vector<std::vector<unsigned>>;


class states
{
public:
    color_matrix colors;
    unsigned W;
    unsigned H;
    states(unsigned w, unsigned h);
    unsigned get_color(unsigned i, unsigned j) const;
    void set_color(unsigned i, unsigned j, unsigned col);
    bool check_x(unsigned n, unsigned i, unsigned j, unsigned col) const;
    bool check_y(unsigned n, unsigned i, unsigned j, unsigned col) const;
};
#endif //BML_STATES_H