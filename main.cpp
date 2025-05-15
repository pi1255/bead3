#include "app.hpp"

class MyApp: public App {
protected
}


int main() {
    MyApp a;
    a.event_loop();
}