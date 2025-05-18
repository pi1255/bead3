#include "statictext.hpp"
#include <sstream>

using namespace genv;
using namespace std;

void StaticText::draw() {
    if(!show) return;
    int fasc = (gout.cascent()+gout.cdescent())/2;
    stringstream ss;
    ss << _txt;
    gout << move_to(x, y+sy/2-fasc) << color (255, 255, 255) << text(ss.str());
}

void StaticText::handle(event ev) {};

