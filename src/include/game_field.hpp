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
    game_field(game_field*);

    bool get(int, int);
    void set(int, int, bool);
    int neighbors(int, int);

    int width();
    int height();

    void print();

private:
    void init(std::vector<std::string>);

    std::vector<bool> field;
    std::vector<std::string> lines;

    int _width;
    int _height;
};

#endif
