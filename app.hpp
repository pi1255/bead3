#ifndef APP_HPP
#define APP_HPP

#include <vector>
#include "graphics.hpp"
#include "colors.hpp"

class Widget;

class App {
protected:
    const unsigned int SCREEN_X;
    const unsigned int SCREEN_Y;
    genv::color bgcolor;
    std::vector<Widget*> widgets;
    genv::canvas background;
public: 
    App(int x, int y, genv::color bgcolor);
    ~App();
    void registre_widget(Widget* w);
    void event_loop();
    inline unsigned int X() {return SCREEN_X;};
    inline unsigned int Y() {return SCREEN_Y;};
};

#endif