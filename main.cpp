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

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream&out, std::map<T1, T2> &t) {
    for(auto i: t) out << i.first << ":" << i.second << std::endl;
    return out;
}

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
    std::set<int> unique;
    for (auto i : s) unique.insert(i);
    std::vector<int> v;
    for(auto i: unique) v.push_back(i);
    if (v.size() > 5)
    for (int i = 1; i < v.size(); i++) {
        if (v[i-1]+1 == v[i]) {
            straight++;
            if (straight == 5) return 1;
        } else straight = 1;
    }
    return 0;
}

int get_multiplier(std::vector<Card*>& cards) {
    std::map<order, bool> found;
    std::map<char, int> suit_count;
    std::map<int, int> value_count;
    std::vector<int> values;

    for (auto card : cards) {
        cardVal val = card->getVal();
        int num;

        if ('2' <= val.num && val.num <= '9') num = val.num - '0';
        else {
            switch (val.num) {
                case 't': num = 10; break;
                case 'j': num = 11; break;
                case 'q': num = 12; break;
                case 'k': num = 13; break;
                case 'a': num = 14; values.push_back(1); break;
                default: num = 0; break;
            }
        }

        values.push_back(num);
        suit_count[val.cardcolor]++;
        value_count[num]++;
    }

    found[flush] = false;
    for (auto suit : suit_count) {
        if (suit.second >= 5) {
            found[flush] = true;
            break;
        }
    }

    found[fourof] = false;
    int four_val = -1;
    for (auto val : value_count) {
        if (val.second >= 4) {
            found[fourof] = true;
            four_val = val.first;
            break;
        }
    }

    found[threeof] = false;
    int three_val = -1;
    for (auto val : value_count) {
        if (val.second >= 3 && val.first != four_val) {
            found[threeof] = true;
            three_val = val.first;
        }
    }

    int pair_count = 0;
    for (auto val : value_count) {
        if (val.second >= 2 && val.first != four_val && val.first != three_val) {
            pair_count++;
        }
    }

    found[pair1] = pair_count >= 1;
    found[pair2] = pair_count >= 2;

    found[full] = false;
    int full_pair_val = -1;
    for (auto val : value_count) {
        if (val.second >= 3) {
            if (three_val == -1 || val.first > three_val) three_val = val.first;
        }
    }
    for (auto val : value_count) {
        if (val.first != three_val && val.second >= 2) {
            full_pair_val = val.first;
            break;
        }
    }
    found[full] = (three_val != -1 && full_pair_val != -1);

    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    found[straight] = false;
    if (values.size() >= 5) {
        int cons = 1;
        for (size_t i = 1; i < values.size(); ++i) {
            if (values[i] == values[i - 1] + 1) {
                cons++;
                if (cons >= 5) {
                    found[straight] = true;
                    break;
                }
            } else {
                cons = 1;
            }
        }
    }
    found[straight_flush] = found[straight] && found[flush];

    found[nothing] = true;

    int max_rank = nothing;
    for (auto f : found) {
        if (f.second && f.first > max_rank) {
            max_rank = f.first;
        }
    }
    std::cout << found;
    return max_rank;
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
        std::string s;
        switch (multiplier) {
            case nothing:
                s= "nothing.";
                break;
            case pair1:
                s ="1 pair.";
                break;
            case pair2:
                s="2 pair.";
                break;
            case threeof:
                s="three of kind.";
                break;
            case flush:
                s="flush.";
                break;
            case straight:
                s = "straight.";
            case full:
                s = "full house.";
                break;
            case fourof:
                s = "four of kind.";
                break;
            case straight_flush:
                s = "straight flush.";
            default:
                break;
        }
        std::stringstream ss;
        if (multiplier*pot) ss << "You won "<< multiplier*pot << "$(You have a " << s << ")" << std::endl
            << "Should I deal another hand?";
        else ss << "You lost " << pot << "$" << std::endl
            << "Should I deal another hand?";
        idx = 0;
        flopped = 0;
        //for (auto i: cards) i->hide();
        players.clear();
        global.clear();
        end = new StaticText(this, 500, 300, SCREEN_X-500, 200, ss.str());
        playagain = new Button(this, 500, 450, 50, 30, (std::string)"Yes!", [&](){end->hide(); playagain->hide(); close->hide();writebalance(); pot = 100; bal -= 100; srand(time(0)); std::random_shuffle(cards.begin(), cards.end()), flop();}, false);
        close = new Button(this, 600, 450, 50, 30, (std::string)"No!", [&](){quit = 1;}, false);
    };
};

/**
 * @param argv[1] can set the amount of balance
 */
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