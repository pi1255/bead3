#ifndef CARD_HPP
#define CARD_HPP

#include "../app.hpp"
#include "widget.hpp"

class Card: public Widget {
protected:
    genv::canvas card;
    char cardcolor; //C, D, H, S
    char num;
    int sizex, sizey;
public:
    Card(App* parent, char col, char num, int x, int y);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;
};


#endif