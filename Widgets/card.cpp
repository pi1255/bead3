#include "card.hpp"
#include <fstream>
#include <sstream>
using namespace std;
using namespace genv;

Card::Card(App* parent, char col, char num, int x, int y): Widget(parent, x, y, 0, 0), cardcolor(col), num(num) {
    //card.transparent(true);
    show = 0;
    stringstream ss;
    std::stringstream s;
    if (num == 't') s << "10";
    else s << num;
    ss << "cards/" << cardcolor << s.str() << ".bmp.kep";
    ifstream f(ss.str());
    if (!f.is_open()) {
        stringstream ss;
        ss << "I/O error at line " << __LINE__  << "(" << cardcolor << "/" << num << ")";
        gout.message(ss.str());
        exit(1);
    }
    f >> sizex >> sizey;
    card.open(sizex, sizey);
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            int r, g, b;
            f >> r>>g>>b;
            card << move_to(j, i) << color(r, g, b) << dot;
        }
    }
    f.close();
    sx = sizex, sy = sizey;
    parent->registre_widget(this);
}

void Card::draw()  {
    if (show) gout << stamp(card, x, y);
}

void Card::handle(event ev) {}