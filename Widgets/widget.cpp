#include "widget.hpp"

Widget::Widget(App* parent,int x, int y, int sx , int sy): parent(parent), x(x), y(y), sx(sx), sy(sy) {
    parent->registre_widget(this);
}

bool Widget::is_selected(int px, int py) {
    return x <= px && px <= x+sx && y <= py && py <= y+sy;
}