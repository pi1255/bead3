#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include <functional>

class Button : public Widget {
protected:
    std::string txt;
    std::function<void()> f;
    bool pressed = false;
    bool stay;
public:
    Button(App* parent, int x, int y, int sx, int sy, std::string text, std::function<void()> f, bool stay);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    inline void press() {pressed = 0;};
};

#endif