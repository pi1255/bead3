#include "app.hpp"
#include "Widgets/widget.hpp"
#include "Widgets/card.hpp"
#include "Widgets/button.hpp"
#include "Widgets/numericin.hpp"
#include <fstream>
#include <sstream>

class MyApp: public App {
protected:
    int bal;
    int pot;
    std::ifstream f;
    Button* nextcard;
    Button* call;
    std::vector<Card*> cards;
        Widget * da;
        Widget * d2; 
        Widget * d3; 
        Widget * d4; 
        Widget * d5; 
        Widget * d6; 
        Widget * d7; 
        Widget * d8; 
        Widget * d9; 
        Widget * d10;
        Widget * dj; 
        Widget * dd; 
        Widget * dk; 
        Widget * ca; 
        Widget * c2; 
        Widget * c3; 
        Widget * c4; 
        Widget * c5; 
        Widget * c6; 
        Widget * c7; 
        Widget * c8; 
        Widget * c9; 
        Widget * c10;
        Widget * cj; 
        Widget * cd; 
        Widget * ck; 
        Widget * ha; 
        Widget * h2; 
        Widget * h3; 
        Widget * h4; 
        Widget * h5; 
        Widget * h6; 
        Widget * h7; 
        Widget * h8; 
        Widget * h9; 
        Widget * h10;
        Widget * hj; 
        Widget * hd; 
        Widget * hk; 
        Widget * sa; 
        Widget * s2; 
        Widget * s3; 
        Widget * s4; 
        Widget * s5; 
        Widget * s6; 
        Widget * s7; 
        Widget * s8; 
        Widget * s9; 
        Widget * s10;
        Widget * sj; 
        Widget * sd; 
        Widget * sk; 
        Numericin* money;
public:
    MyApp(int x, int y) : App(x, y, GREEN) {
        f.open("balance.txt");
        if (!f.is_open()) {
            std::stringstream ss;
            ss << "I/O error at line " << __LINE__;
            genv::gout.message(ss.str());
            exit(1);
        }
        f >> bal;
        da = new Card(this, 'D', "a", 10, 10);
        d2 = new Card(this, 'D', "2", 10, 10);
        d3 = new Card(this, 'D', "3", 10, 10);
        d4 = new Card(this, 'D', "4", 10, 10);
        d5 = new Card(this, 'D', "5", 10, 10);
        d6 = new Card(this, 'D', "6", 10, 10);
        d7 = new Card(this, 'D', "7", 10, 10);
        d8 = new Card(this, 'D', "8", 10, 10);
        d9 = new Card(this, 'D', "9", 10, 10);
        d10 = new Card(this, 'D', "10", 10, 10);
        dj = new Card(this, 'D', "j", 10, 10);
        dd = new Card(this, 'D', "q", 10, 10);
        dk = new Card(this, 'D', "k", 10, 10);
        ca = new Card(this, 'C', "a", 10, 10);
        c2 = new Card(this, 'C', "2", 10, 10);
        c3 = new Card(this, 'C', "3", 10, 10);
        c4 = new Card(this, 'C', "4", 10, 10);
        c5 = new Card(this, 'C', "5", 10, 10);
        c6 = new Card(this, 'C', "6", 10, 10);
        c7 = new Card(this, 'C', "7", 10, 10);
        c8 = new Card(this, 'C', "8", 10, 10);
        c9 = new Card(this, 'C', "9", 10, 10);
        c10 = new Card(this, 'C', "10", 10, 10);
        cj = new Card(this, 'C', "j", 10, 10);
        cd = new Card(this, 'C', "q", 10, 10);
        ck = new Card(this, 'C', "k", 10, 10);
        ha = new Card(this, 'H', "a", 10, 10);
        h2 = new Card(this, 'H', "2", 10, 10);
        h3 = new Card(this, 'H', "3", 10, 10);
        h4 = new Card(this, 'H', "4", 10, 10);
        h5 = new Card(this, 'H', "5", 10, 10);
        h6 = new Card(this, 'H', "6", 10, 10);
        h7 = new Card(this, 'H', "7", 10, 10);
        h8 = new Card(this, 'H', "8", 10, 10);
        h9 = new Card(this, 'H', "9", 10, 10);
        h10 = new Card(this, 'H', "10", 10, 10);
        hj = new Card(this, 'H', "j", 10, 10);
        hd = new Card(this, 'H', "q", 10, 10);
        hk = new Card(this, 'H', "k", 10, 10);
        sa = new Card(this, 'S', "a", 10, 10);
        s2 = new Card(this, 'S', "2", 10, 10);
        s3 = new Card(this, 'S', "3", 10, 10);
        s4 = new Card(this, 'S', "4", 10, 10);
        s5 = new Card(this, 'S', "5", 10, 10);
        s6 = new Card(this, 'S', "6", 10, 10);
        s7 = new Card(this, 'S', "7", 10, 10);
        s8 = new Card(this, 'S', "8", 10, 10);
        s9 = new Card(this, 'S', "9", 10, 10);
        s10 = new Card(this, 'S', "10", 10, 10);
        sj = new Card(this, 'S', "j", 10, 10);
        sd = new Card(this, 'S', "q", 10, 10);
        sk = new Card(this, 'S', "k", 10, 10);
        money = new Numericin(this, 150, SCREEN_Y-150, 100, 50, 0, bal);
        //void (*fun) () = _call;
        call = new Button(this, 50, SCREEN_Y-150, 50, 50, "Call", [&](){
            int a = money->getval();
            bal-a;
            //nextcard->press();
        }, false);
        nextcard = new Button(this, 300, SCREEN_Y-150, 100, 50, "Next card!", [](){}, false);
    };
    ~MyApp(){ f.close();};
    void nextCard(){

    };
    void _call() {
        int a = money->getval();
        bal-a;
        nextcard->press();
    }
};


int main() {
    MyApp a(1280, 720);
    a.event_loop();
}