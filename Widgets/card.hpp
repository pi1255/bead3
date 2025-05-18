#ifndef CARD_HPP
#define CARD_HPP

#include "../app.hpp"
#include "widget.hpp"
#include <string>

struct cardVal {
    char cardcolor;
    std::string num;
};

class Card: public Widget {
protected:
    genv::canvas card;
    char cardcolor; //C, D, H, S
    std::string num;
    int sizex, sizey;
    bool show = false;
public:
    Card(App* parent, char col, std::string num, int x, int y);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    void setposition(int _x, int _y) {x = _x, y =_y; show = true;};
    inline cardVal getVal() const {return {cardcolor, num};};
    inline void clean() {show =false;};
};


#endif