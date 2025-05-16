#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "../app.hpp"

class Widget {
protected:
    App* parent;
    int x,y, sx, sy;
public:
    Widget(App* parent, int x, int y, int sx, int sy);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
    bool is_selected(int px, int py);
};

#endif