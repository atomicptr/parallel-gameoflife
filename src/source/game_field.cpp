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

    this->_width = size[0];
    this->_height = size[1];

    for_each(lines.begin(), lines.end(), [&](string &s) {
        auto tmp = utils::split(s, ' ');

        for_each(tmp.begin(), tmp.end(), [&](string &c) {
            this->field.push_back(c == "1" ? true : false);
        });
    });
}

bool game_field::get(int x, int y) {
    return this->field[this->_width * y + x];
}

void game_field::set(int x, int y, bool value) {
    this->field[this->_width * y + x] = value;
}

int game_field::neighbors(int x, int y) {
    int neighbor_counter = 0;

    // for every neighbor
    for(int j = y - 1; j <= y + 1; j++) {
        for(int i = x - 1; i <= x + 1; i++) {

            if(i >= 0 && j >= 0 && i < this->_width && j < this->_height && !(i == x && j == y)) {

                // if neighbor is alive
                if(get(i, j)) {
                    neighbor_counter++;
                }
            }
        }
    }

    return neighbor_counter;
}

int game_field::width() {
    return this->_width;
}

int game_field::height() {
    return this->_height;
}

void game_field::print() {
    int counter = 0;

    for_each(this->field.begin(), this->field.end(), [&](bool b) {
        if(counter >= _width) {
            counter = 0;
            cout << endl;
        }

        cout << (b ? "1" : "0") << " ";

        counter++;
    });

    cout << endl;
}
