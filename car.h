#ifndef BML_CAR_H
#define BML_CAR_H

class car
{
public:
    unsigned x;
    unsigned y;

    void move_x(int s)
    {
        x += s;
        x = x % H;
    }
    void move_y(int s)
    {
        y += s;
        y = y % W;
    }

    car(unsigned X, unsigned Y) :
            x(X),
            y(Y) {};
};

#endif //BML_CAR_H
