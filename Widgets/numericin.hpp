#ifndef NUMERICIN_HPP
#define NUMERICIN_HPP

#include "widget.hpp"

class Numericin : public Widget {
protected:
    int minval;
    int maxval;
    int val;
    bool mouse_pressed = false;
    int left_size;
    int right_size ;
    bool write = false;
    bool neg = true;
public:
    Numericin(App*p,  int x, int y, int sx, int sy, int minval, int maxval, int val);
    Numericin(App* p, int x, int y, int sx, int sy, int minval, int maxval);
    virtual void handle(genv::event) override;
    virtual void draw() override;
    inline int getval() const {return val;};
    void updatemax(int x) {maxval = x;};
};


#endif