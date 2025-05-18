#include "button.hpp"
#include <algorithm>
using namespace genv;
using namespace std;

Button::Button(App* parent, int x, int y, int sx, int sy, std::string text, std::function<void()>f, bool stay): Widget(parent, x, y, sx, sy), txt(text), f(f), stay(stay) {};

void Button::draw() {
    gout << move_to(x, y) << (pressed? ROYAL_BLUE : LIGHT_BLUE) << box(sx, sy);
    gout << BLACK;
    int casc = (gout.cascent()+gout.cdescent())/2;
    int l = gout.twidth(txt);
    if (l < sx) {
        gout << move_to(x+sx/2-l/2, y+sy/2-casc*2/3) << text(txt);
    }
    if (pressed && !stay) pressed = 0;
}

void Button::handle(event ev) {
    if (!pressed) {
        f();
        pressed = true;
    }
}
