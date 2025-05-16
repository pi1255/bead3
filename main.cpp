#include "app.hpp"
#include "Widgets/widget.hpp"
#include "Widgets/card.hpp"
#include <fstream>

class MyApp: public App {
public:
    MyApp(int x, int y) : App(x, y, GREEN) {
        Widget * da = new Card(this, 'H', 'a', 10, 10);
    };
};


int main() {
    MyApp a(1280, 720);
    a.event_loop();
}