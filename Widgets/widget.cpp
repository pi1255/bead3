#include "widget.hpp"
#include <fstream>
#include <sstream>
using namespace std;
using namespace genv;

Widget::Widget(App* parent, char col, char num, int x, int y, int sx , int sy): parent(parent), cardcolor(col), num(num), x(x), y(y), sx(sx), sy(sy) {
    card.open(parent->X(), parent->Y());
    card.transparent(true);
    stringstream ss;
    ss << "cards/" << cardcolor << num << ".bmp.kep";
    ifstream f(ss.str());
    int _x, _y;
    if (!f.is_open()) {
        stringstream ss;
        ss << "I/O error at line " << __LINE__;
        gout.message(ss.str());
        exit(1);
    }
    f >> _x >> _y;
    for (int i = 0; i < _x; i++) {
        for (int j = 0; j < y; j++) {
            int r, g, b;
            f >> r>>g>>b;
            card << move_to(i, j) << color(r, g, b) << dot;
        }
    }
    f.close();
    parent->registre_widget(this);
}

bool Widget::is_selected(int px, int py) {
    return x <= px && px <= x+sx && y <= py && py <= y+sy;
}