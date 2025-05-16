#include "card.hpp"
#include <fstream>
#include <sstream>
using namespace std;
using namespace genv;

Card::Card(App* parent, char col, char num, int x, int y): Widget(parent, x, y, 0, 0), cardcolor(col), num(num) {
    card.open(parent->X(), parent->Y());
    card.transparent(true);
    stringstream ss;
    ss << "cards/" << cardcolor << num << ".bmp.kep";
    ifstream f(ss.str());
    if (!f.is_open()) {
        stringstream ss;
        ss << "I/O error at line " << __LINE__;
        gout.message(ss.str());
        exit(1);
    }
    f >> sizex >> sizey;
    for (int i = 0; i < sizex; i++) {
        for (int j = 0; j < sizey; j++) {
            int r, g, b;
            f >> r>>g>>b;
            card << move_to(i, j) << color(r, g, b) << dot;
        }
    }
    f.close();
    sx = sizex, sy = sizey;
    parent->registre_widget(this);
}

void Card::draw()  {
    gout << stamp(card, x, y);
}

void Card::handle(event ev) {}