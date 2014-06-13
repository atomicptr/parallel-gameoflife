#include <game_field.hpp>

using namespace std;

game_field::game_field(string filename) {
    auto lines = utils::get_lines(filename);

    this->init(lines);
}

game_field::game_field(vector<string> lines) {
    this->init(lines);
}

void game_field::init(vector<string> lines) {
    auto size = utils::get_size(lines);

    this->width = size[0];
    this->height = size[1];

    for_each(lines.begin(), lines.end(), [&](string &s) {
        auto tmp = utils::split(s, ' ');

        for_each(tmp.begin(), tmp.end(), [&](string &c) {
            this->field.push_back(c == "1" ? true : false);
        });
    });
}

bool game_field::get(int x, int y) {
    return this->field[this->width * y + x];
}

void game_field::set(int x, int y, bool value) {
    this->field[this->width * y + x] = value;
}

void game_field::print() {
    int counter = 0;

    for_each(this->field.begin(), this->field.end(), [&](bool b) {
        if(counter >= width) {
            counter = 0;
            cout << endl;
        }

        cout << (b ? "1" : "0") << " ";

        counter++;
    });

    cout << endl;
}
