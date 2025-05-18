#include "app.hpp"
#include "Widgets/widget.hpp"
#include <iostream>
using namespace genv;
using std::vector;

App::App(int x, int y, color bgcolor = GREEN): SCREEN_X(x), SCREEN_Y(y), bgcolor(bgcolor) {
    gout.open(SCREEN_X, SCREEN_Y);
    background.open(SCREEN_X, SCREEN_Y);
    background << move_to(0, 0) << bgcolor << box(SCREEN_X, SCREEN_Y);
    gout << stamp(background, 0,0);
    gout << refresh;
}

App::~App() {
    //for (auto i: widgets) delete i;
}

void App::event_loop() {
    event ev;
    int focus = -1;
    gout << stamp(background, 0, 0);
    for (auto i: widgets) i->draw();
    gout << refresh;
    while (gin >> ev && ev.keycode != key_escape) {
        gout << stamp(background, 0, 0);
        if (ev.button == btn_left) {
            for (int i = 0; i < widgets.size(); i++) {
                if (widgets.at(i)->is_selected(ev.pos_x, ev.pos_y)) focus = i;
            }
        }
        if (ev.keycode == key_tab && focus != -1) {
            focus++;
            if (focus >= widgets.size()) focus = 0;
        }
        if (focus != -1) widgets.at(focus)->handle(ev);
        gout << stamp(background, 0,0);
        for (auto i: widgets) i->draw();
        gout << refresh;
    }
}

void App::registre_widget(Widget* w) {
    widgets.push_back(w);
}