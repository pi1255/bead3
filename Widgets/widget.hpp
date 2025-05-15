#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "../app.hpp"

class Widget {
protected:
    App* parent;
    genv::canvas card;
    char cardcolor; //C, D, H, S
    char num;
    int x,y, sx, sy;
public:
    Widget(App* parent, char col, char num, int x, int y, int sx, int sy);
    virtual void draw() const = 0;
    virtual void handle(genv::event ev) = 0;
    bool is_selected(int px, int py);
};


#endif