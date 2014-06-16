#include <iostream>
#include <string>
#include <utils.hpp>
#include <game_field.hpp>

using namespace std;
using namespace utils;

int main() {
    int number_of_generations = 100;
    string input_file = "input_file.txt";
    int number_of_threads = 1;

    game_field *field = new game_field(input_file);
    game_field *next;

    for(int i = 0; i < number_of_generations; i++) {
        next = new game_field(field);

        for(int y = 0; y < field->height(); y++) {
            for(int x = 0; x < field->width(); x++) {
                bool alive = field->get(x, y);
                int neighbors = field->neighbors(x, y);

                if(alive && neighbors < 2) {
                    next->set(x, y, false);
                } else if(alive && neighbors > 3) {
                    next->set(x, y, false);
                } else if(alive && (neighbors == 2 || neighbors == 3)) {
                    // do nothing
                } else if(!alive && neighbors == 3) {
                    next->set(x, y, true);
                }
            }
        }

        delete field;
        field = next;
    }

    field->print();

    delete field;

    return 0;
}
