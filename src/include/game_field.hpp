#ifndef __GAME_FIELD_HPP__
#define __GAME_FIELD_HPP__

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <utils.hpp>

class game_field {

public:
    game_field(std::string);
    game_field(std::vector<std::string>);
    game_field(const game_field&);

    bool get(int, int);
    void set(int, int, bool);
    int neighbors(int, int);

    int width();
    int height();

    void print();
std::vector<bool> field;
private:
    void init(std::vector<std::string>);

    int _width;
    int _height;
};

#endif
