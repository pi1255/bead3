#include "app.hpp"
#include "Widgets/widget.hpp"
#include "Widgets/card.hpp"
#include "Widgets/button.hpp"
#include "Widgets/numericin.hpp"
#include "Widgets/statictext.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

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
public:
    MyApp(int x, int y) : App(x, y, genv::color(0, 81, 44)) {
        f.open("balance.txt");
        if (!f.is_open()) {
            std::stringstream ss;
            ss << "I/O error at line " << __LINE__;
            genv::gout.message(ss.str());
            exit(1);
        }
        f >> bal;
        {
        cards.push_back(new Card(this, 'D', "a", 10, 10));
        cards.push_back(new Card(this, 'D', "2", 10, 10));
        cards.push_back(new Card(this, 'D', "3", 10, 10));
        cards.push_back(new Card(this, 'D', "4", 10, 10));
        cards.push_back(new Card(this, 'D', "5", 10, 10));
        cards.push_back(new Card(this, 'D', "6", 10, 10));
        cards.push_back(new Card(this, 'D', "7", 10, 10));
        cards.push_back(new Card(this, 'D', "8", 10, 10));
        cards.push_back(new Card(this, 'D', "9", 10, 10));
        cards.push_back( new Card(this, 'D', "10", 10, 10));
        cards.push_back(new Card(this, 'D', "j", 10, 10));
        cards.push_back(new Card(this, 'D', "q", 10, 10));
        cards.push_back(new Card(this, 'D', "k", 10, 10));
        cards.push_back(new Card(this, 'C', "a", 10, 10));
        cards.push_back(new Card(this, 'C', "2", 10, 10));
        cards.push_back(new Card(this, 'C', "3", 10, 10));
        cards.push_back(new Card(this, 'C', "4", 10, 10));
        cards.push_back(new Card(this, 'C', "5", 10, 10));
        cards.push_back(new Card(this, 'C', "6", 10, 10));
        cards.push_back(new Card(this, 'C', "7", 10, 10));
        cards.push_back(new Card(this, 'C', "8", 10, 10));
        cards.push_back(new Card(this, 'C', "9", 10, 10));
        cards.push_back( new Card(this, 'C', "10", 10, 10));
        cards.push_back(new Card(this, 'C', "j", 10, 10));
        cards.push_back(new Card(this, 'C', "q", 10, 10));
        cards.push_back(new Card(this, 'C', "k", 10, 10));
        cards.push_back(new Card(this, 'H', "a", 10, 10));
        cards.push_back(new Card(this, 'H', "2", 10, 10));
        cards.push_back(new Card(this, 'H', "3", 10, 10));
        cards.push_back(new Card(this, 'H', "4", 10, 10));
        cards.push_back(new Card(this, 'H', "5", 10, 10));
        cards.push_back(new Card(this, 'H', "6", 10, 10));
        cards.push_back(new Card(this, 'H', "7", 10, 10));
        cards.push_back(new Card(this, 'H', "8", 10, 10));
        cards.push_back(new Card(this, 'H', "9", 10, 10));
        cards.push_back( new Card(this, 'H', "10", 10, 10));
        cards.push_back(new Card(this, 'H', "j", 10, 10));
        cards.push_back(new Card(this, 'H', "q", 10, 10));
        cards.push_back(new Card(this, 'H', "k", 10, 10));
        cards.push_back(new Card(this, 'S', "a", 10, 10));
        cards.push_back(new Card(this, 'S', "2", 10, 10));
        cards.push_back(new Card(this, 'S', "3", 10, 10));
        cards.push_back(new Card(this, 'S', "4", 10, 10));
        cards.push_back(new Card(this, 'S', "5", 10, 10));
        cards.push_back(new Card(this, 'S', "6", 10, 10));
        cards.push_back(new Card(this, 'S', "7", 10, 10));
        cards.push_back(new Card(this, 'S', "8", 10, 10));
        cards.push_back(new Card(this, 'S', "9", 10, 10));
        cards.push_back( new Card(this, 'S', "10", 10, 10));
        cards.push_back(new Card(this, 'S', "j", 10, 10));
        cards.push_back(new Card(this, 'S', "q", 10, 10));
        cards.push_back(new Card(this, 'S', "k", 10, 10));
        }
        std::random_shuffle(cards.begin(), cards.end()-1);
        Card* c1 = *(cards.end()-(idx++)-1);
        c1->setposition(500, 500);
        //cards.pop_back();
        Card* c2 = *(cards.end()-(idx++)-1);
        c2->setposition(600, 500);
        //cards.pop_back();
        players.push_back(c1);
        players.push_back(c2);
        flop();
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
        nextcard = new Button(this, 300, SCREEN_Y-150, 100, 50, "Next card!", [&](){turn();}, false);
        std::stringstream ss;
        ss << "Pot: " << pot << std::endl << "Yo have: " << bal;
        st = new StaticText(this, 800, SCREEN_Y -150, SCREEN_X-800, 50, ss.str());
    };
    ~MyApp(){
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
    };
    void flop() {
        for ( int i = 0; i < 3 && cards.size() > 1; i++) {
            Card*c = *(cards.end()-(idx++)-1);
            c->setposition(150 + 100*i, 50);
            //cards.pop_back();
            players.push_back(c);
            flopped++;
        }
    };
    void turn() {
        if (flopped < 5) {
            Card*c = *(cards.end()-(idx++)-1);
            c->setposition(150 + 100*(flopped++), 50);
            //cards.pop_back();
            players.push_back(c);
        }
    }
    void post() {
        if (flopped == 5) {
            unsigned multiplier = 0;
            /*
            nothing
            1 pair
            2 par
            three of kind
            flush
            straight
            full house
            4 of kind
            stright flush
            royal flush
            */
            std::map<std::string, int>  found;
            std::vector<cardVal> v;
            for (auto i: cards) v.push_back(i->getVal());
            std::map<char, int> m;
            for(auto i: v) {
                if (m.at(i.cardcolor)) m[i.cardcolor]++;
                else m[i.cardcolor] = 1;
            }
            std::map<std::string, int> m2;
            for (auto i:v) {
                if (m2.at(i.num)) m2[i.num]++;
                else m2[i.num] = 1;
            }
            for (auto i: m2) {
                if (i.second == 2) {
                    if (found.at("threeof") == 1) found["full"] = 1;
                    else if (found.at("pair")) found.at("pair")++;
                    else found["pair"] = 1;
                }
                if (i.second == 3) {
                    if (found.at("pair") == 1) found["full"] = 1;
                    else found["threeof"] = 1; 
                }
                if (i.second == 4) {
                    found["fourof"] = 1;
                }
            }
            for (auto i: m) {
                if (i.second >= 5) {
                    found["flush"] = 1;
                    for (int j = 1; j <= 8; j++) {
                        for (int k = 0; k < 5; k++) {
                            
                        }
                    }
                }
            }


            bal += multiplier*pot;
            idx = 0;
            flopped = 0;
            //for (auto i: cards) i->clean();
            //players.clear();
            //global.clear();
        }
    };
};


int main() {
    srand(time(0));
    MyApp a(1280, 720);
    a.event_loop();
}