#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP
#include "widget.hpp"
#include <string>
class StaticText : public Widget {
protected:
    std::string _txt;
public:
    StaticText(App* p, int x, int y, int sx, int sy, std::string s): Widget(p, x, y, sx, sy), _txt(s) {} ;
    virtual void draw() override ;
    virtual void handle(genv::event ev) override;
    void setString(std::string & s) {_txt = s;};
};


#endif