#include "app.hpp"
#include "Widgets/widget.hpp"
#include "Widgets/card.hpp"
#include "Widgets/button.hpp"
#include "Widgets/numericin.hpp"
#include "Widgets/statictext.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>

enum order{
    nothing = 0,
    pair1, pair2,
    threeof,
    flush, straight,
    full, fourof,
    straight_flush
};

bool isstraight(std::vector<int>&s) {
    int straight = 1;
    if (s.size()< 5)
    for (int i = 1; i < s.size(); i++) {
        if (s[i-1]+1 == s[i]) {
            straight++;
            if (straight == 5) return 1;
        } else straight = 1;
    }
    return 0;
}

int get_multiplier(std::vector<Card*>& cards) {
    unsigned multiplier = 0;
    std::map<order, bool> found;
    std::vector<cardVal> v;
    for (auto i: cards) v.push_back(i->getVal());
    std::vector<int> s;
    for (auto i: v) {
        if ('2' <= i.num && i.num <= '9') s.push_back(i.num-'0');
        else {
            switch (i.num) {
                case 't':
                    s.push_back(10);
                    break;
                case 'j':
                    s.push_back(11);
                    break;
                case 'q':
                    s.push_back(12);
                    break;
                case 'k':
                    s.push_back(13);
                case 'a':
                    s.push_back(14);
                    s.push_back(1);
                    break;
            }
        }
    }
    std::sort(s.begin(), s.end());
    std::map<char, int> m;
    for(auto i: v) {
        try {m.at(i.cardcolor)++;}
        catch (std::out_of_range &e) { m[i.cardcolor] = 1;}
    }
    found[flush] = 0;
    for (auto i: m) {
        if (i.second >= 5) found[flush] = 1;
    }
    found[fourof] = 0;
    int poker= 0, three =0;
    for (int i = 3; i < s.size(); i++) {
        if (s[i] == s[i-1] && s[i]== s[i-2] && s[i-3]== s[i] && s[i]!= 1) {
            found[fourof] = 1;
            poker = s[1];
        }
    }
    found[threeof] = 0;
    for (int i = 2; i < s.size(); i++) {
        if(s[i-1] == s[i] && s[i] == s[i-2] && s[i] != 1 && s[i] == poker) {
            found[threeof] = 1;
            three = s[i];
        }
    }
    found[pair1] = 0;
    found[pair2] = 0;
    for (int i = 1; i < s.size(); i++) {
        if(s[i-1] == s[i] && s[i] != 1 && s[i] != three && s[i] != poker) {
            if (found[pair1] == 1) {found[pair2] = 1;}
            else found[pair1] = 1;
        }
    }
    found[full] = found[pair1] && found[threeof];
    found[order::straight] = isstraight(s);
    
    for (auto i: m) {
        if (i.second >= 5) {
            found[flush] = 1;
        }
    }
    found[straight_flush]= found[straight] && found[flush];
    found[nothing]= 1;
    std::vector<int> w;
    for (auto i : found) {
        if (i.second) w.push_back(i.first);
    }
    std::sort(w.begin(), w.end());
    multiplier = w.at(w.size()-1);

    
    return multiplier;

}

class MyApp: public App {
protected:
    int bal;
    int pot = 0;
    std::ifstream f;
    Button* nextcard;
    Button* call;
    std::vector<Card*> cards;
    Numericin* money;
    std::vector<Card*> players;
    std::vector<Card*> global;
    int flopped = 0;
    StaticText * st;
    int idx = 0;
    StaticText *end;
    Button* playagain;
    Button* close;
public:
    MyApp(int x, int y, int setbal) : App(x, y, genv::color(0, 81, 44)) {
        f.open("balance.txt");
        if (!f.is_open()) {
            std::stringstream ss;
            ss << "I/O error at line " << __LINE__;
            genv::gout.message(ss.str());
            exit(1);
        }
        if (setbal == 0) f >> bal;
        else bal = setbal;
        {
        cards.push_back(new Card(this, 'D', 'a', 10, 10));
        cards.push_back(new Card(this, 'D', '2', 10, 10));
        cards.push_back(new Card(this, 'D', '3', 10, 10));
        cards.push_back(new Card(this, 'D', '4', 10, 10));
        cards.push_back(new Card(this, 'D', '5', 10, 10));
        cards.push_back(new Card(this, 'D', '6', 10, 10));
        cards.push_back(new Card(this, 'D', '7', 10, 10));
        cards.push_back(new Card(this, 'D', '8', 10, 10));
        cards.push_back(new Card(this, 'D', '9', 10, 10));
        cards.push_back(new Card(this, 'D', 't', 10, 10));
        cards.push_back(new Card(this, 'D', 'j', 10, 10));
        cards.push_back(new Card(this, 'D', 'q', 10, 10));
        cards.push_back(new Card(this, 'D', 'k', 10, 10));
        cards.push_back(new Card(this, 'C', 'a', 10, 10));
        cards.push_back(new Card(this, 'C', '2', 10, 10));
        cards.push_back(new Card(this, 'C', '3', 10, 10));
        cards.push_back(new Card(this, 'C', '4', 10, 10));
        cards.push_back(new Card(this, 'C', '5', 10, 10));
        cards.push_back(new Card(this, 'C', '6', 10, 10));
        cards.push_back(new Card(this, 'C', '7', 10, 10));
        cards.push_back(new Card(this, 'C', '8', 10, 10));
        cards.push_back(new Card(this, 'C', '9', 10, 10));
        cards.push_back(new Card(this, 'C', 't', 10, 10));
        cards.push_back(new Card(this, 'C', 'j', 10, 10));
        cards.push_back(new Card(this, 'C', 'q', 10, 10));
        cards.push_back(new Card(this, 'C', 'k', 10, 10));
        cards.push_back(new Card(this, 'H', 'a', 10, 10));
        cards.push_back(new Card(this, 'H', '2', 10, 10));
        cards.push_back(new Card(this, 'H', '3', 10, 10));
        cards.push_back(new Card(this, 'H', '4', 10, 10));
        cards.push_back(new Card(this, 'H', '5', 10, 10));
        cards.push_back(new Card(this, 'H', '6', 10, 10));
        cards.push_back(new Card(this, 'H', '7', 10, 10));
        cards.push_back(new Card(this, 'H', '8', 10, 10));
        cards.push_back(new Card(this, 'H', '9', 10, 10));
        cards.push_back(new Card(this, 'H', 't', 10, 10));
        cards.push_back(new Card(this, 'H', 'j', 10, 10));
        cards.push_back(new Card(this, 'H', 'q', 10, 10));
        cards.push_back(new Card(this, 'H', 'k', 10, 10));
        cards.push_back(new Card(this, 'S', 'a', 10, 10));
        cards.push_back(new Card(this, 'S', '2', 10, 10));
        cards.push_back(new Card(this, 'S', '3', 10, 10));
        cards.push_back(new Card(this, 'S', '4', 10, 10));
        cards.push_back(new Card(this, 'S', '5', 10, 10));
        cards.push_back(new Card(this, 'S', '6', 10, 10));
        cards.push_back(new Card(this, 'S', '7', 10, 10));
        cards.push_back(new Card(this, 'S', '8', 10, 10));
        cards.push_back(new Card(this, 'S', '9', 10, 10));
        cards.push_back(new Card(this, 'S', 't', 10, 10));
        cards.push_back(new Card(this, 'S', 'j', 10, 10));
        cards.push_back(new Card(this, 'S', 'q', 10, 10));
        cards.push_back(new Card(this, 'S', 'k', 10, 10));
        }
        std::random_shuffle(cards.begin(), cards.end()-1);
        flop();
        pot = 100;
        bal -= 100;
        money = new Numericin(this, 150, SCREEN_Y-150, 100, 50, 0, bal);
        //void (*fun) () = _call;
        call = new Button(this, 50, SCREEN_Y-150, 50, 50, "Raise", [&](){
            int a = money->getval();
            if (bal >= a) {
                bal-=a;pot += a;
                std::stringstream ss;
                ss << "Pot: " << pot << std::endl << "You have: " << bal;
                std::string s = ss.str();
                st->setString(s);
            } else {
                genv::gout.message("nincs elg pénzed!");
            }}, false);
        nextcard = new Button(this, 300, SCREEN_Y-150, 100, 50, "Next card!", [&](){
            if (flopped < 3) flop();
            else if( flopped > 2 && flopped < 5) turn();
            else post();
        }, false);
        std::stringstream ss;
        ss << "Pot: " << pot << std::endl << "Yo have: " << bal;
        st = new StaticText(this, 800, SCREEN_Y -150, SCREEN_X-800, 50, ss.str());
    };
    ~MyApp(){
        writebalance();
    };
    void writebalance() {
        f.close();
        std::ofstream out("balance.txt");
        if (!out.is_open()) {
            std::stringstream ss;
            ss << "I/O error at line " << __LINE__;
            genv::gout.message(ss.str());
            exit(1);
        }
        out << bal;
        out.close();
    }
    void flop() {
        Card* c1 = *(cards.end()-(idx++)-1);
        c1->setposition(500, 500);
        Card* c2 = *(cards.end()-(idx++)-1);
        c2->setposition(600, 500);
        players.push_back(c1);
        players.push_back(c2);
        for ( int i = 0; i < 3 && cards.size() > 1; i++) {
            Card*c = *(cards.end()-(idx++)-1);
            c->setposition(150 + 100*i, 50);
            global.push_back(c);
            flopped++;
        }
    };
    void turn() {
        Card*c = *(cards.end()-(idx++)-1);
        c->setposition(150 + 100*(flopped++), 50);
        global.push_back(c);
    }
    void post() {
        std::vector<Card*> tmp;
        for (auto &i: players) tmp.push_back(i);
        for (auto &i: global) tmp.push_back(i);
        int multiplier = get_multiplier(tmp);
        bal += multiplier*pot;
        std::stringstream ss;
        if (multiplier*pot) ss << "You won " << multiplier*pot << "$" << std::endl
            << "Should I deal another hand?";
        else ss << "You lost " << pot << "$" << std::endl
            << "Should I deal another hand?";
        idx = 0;
        flopped = 0;
        for (auto i: cards) i->hide();
        players.clear();
        global.clear();
        end = new StaticText(this, 500, 300, SCREEN_X-500, 200, ss.str());
        playagain = new Button(this, 500, 450, 50, 30, (std::string)"Yes!", [&](){end->hide(); playagain->hide(); close->hide();writebalance(); pot = 100; bal -= 100; srand(time(0)); std::random_shuffle(cards.begin(), cards.end()), flop();}, false);
        close = new Button(this, 600, 450, 50, 30, (std::string)"No!", [&](){quit = 1;}, false);
    };
};


int main(int argc, const char* argv[]) {
    int setbal = 0;
    if (argc > 1) {
        std::stringstream ss;
        ss<<argv[1];
        ss >> setbal;
    }
    srand(time(0));
    MyApp a(1280, 720, setbal);
    a.event_loop();
}