#include"numericin.hpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace genv;

Numericin::Numericin(App*p, int x, int y, int sx, int sy, int minval, int maxval, int val): Widget(p, x, y, sx, sy), minval(minval), maxval(maxval), val(val) {
    right_size = 30, left_size = 10;
};

Numericin::Numericin(App*p, int x, int y, int sx, int sy, int minval, int maxval) : Numericin(p, x, y, sx, sy, minval, maxval, (minval+maxval)/2) {};


void Numericin::draw(){
    gout << color(0, 0, 0) << move_to(x,y) << box(sx, sy);
    gout << color(255, 255, 255) << move_to(x, y) << line(0, sy)<<line(sx, 0)<< line(0, -sy) << line(-sx, 0);
    std::stringstream ss;
    ss << val;
    int casc = (gout.cascent()+gout.cdescent())/2;
    int len = gout.twidth(ss.str());
    gout << move_to(x+right_size, y) << line(0, sy)
        << move_to(x+left_size, y+sy/2) << line( left_size, 0);
    if (write) gout << move_to(x+right_size+5, y+sy/2-casc)<< LIGHT_YELLOW << box_to(x+sx-right_size-5, y+sy/2+casc) << BLACK;
    else gout << move_to(x+right_size+5, y+sy/2-casc/2);
    gout << move_to(x+sx/2-len/2, y+sy/2+casc/2) << text(ss.str());
    gout << WHITE << move_to(x+sx-right_size, y) << line(0, sy) << move_to(x+sx-right_size+left_size, y+sy/2)
        << line(right_size-2*left_size, 0) << move_to(x+sx-right_size+2*left_size-left_size/2, y+sy/2-left_size/2) 
        << line(0, left_size);    
};

void Numericin::handle(event ev) {
    int casc = gout.cascent()+gout.cdescent();
    if (ev.keycode == key_down && val > minval) val--;
    if (ev.keycode == key_up && val < maxval) val++;
    if (ev.keycode == key_pgdn && val >= minval+10) val -= 10;
    if (ev.keycode == key_pgup && val <= maxval-10) val += 10;
    if (val < 0) neg = 1;
    if (ev.button == btn_left) {
        if (ev.pos_x >= x+right_size +5 && ev.pos_x < x+sx-right_size-5 && ev.pos_y >= y+sy/2-casc/2 && ev.pos_y <= y+sy/2+casc/2) {
            write = 1;
            val = std::min(maxval, 0);
            neg = 0;
        } 
        else {
            if (ev.pos_x > x && ev.pos_x < x+right_size && ev.pos_y >y && ev.pos_y < y+sy && val > minval) val--;
            if (ev.pos_x < x+sx && ev.pos_x > x+sx-right_size && ev.pos_y >y && ev.pos_y < y+sy && val < maxval) val++;
            write = 0;
        }
    }
    if (write && ((ev.keycode >= 48 && ev.keycode <= 57))) {
        if (0) {
	bool now = 0;
        if (ev.keycode = '-') {
            val = std::max(0, maxval);
            neg = 1;
            now = 1;
        }
        if (neg && !now) val = 10*val - (ev.keycode-48);
        else if (!now) val = 10*val + (ev.keycode-48);
	}
	val = val*10+(ev.keycode - 48);
        if (val > maxval) val = maxval;
        if (val < minval) val = minval;
    }

};

