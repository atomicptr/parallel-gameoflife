#include <iostream>
#include <string>
#include <utils.hpp>
#include <game_field.hpp>

using namespace std;

struct point_t {
    int x;
    int y;
};

int main() {
    int number_of_generations = 1001;
    string input_file = "input_file.txt";
    string output_file = "output_file.txt";
    int number_of_threads = 1;

    game_field field(input_file);

    vector<point_t> to_kill;
    vector<point_t> to_revive;

    for(int i = 0; i < number_of_generations; i++) {
        to_kill.clear();
        to_revive.clear();

        for(int y = 0; y < field.height(); y++) {
            for(int x = 0; x < field.width(); x++) {
                point_t p;

                p.x = x;
                p.y = y;

                bool alive = field.get(x, y);
                int neighbors = field.neighbors(x, y);

                if(alive && neighbors < 2) {
                    to_kill.push_back(p);
                } else if(alive && neighbors > 3) {
                    to_kill.push_back(p);
                } else if(alive && (neighbors == 2 || neighbors == 3)) {
                    // do nothing
                } else if(!alive && neighbors == 3) {
                    to_revive.push_back(p);
                }
            }
        }

        for_each(to_kill.begin(), to_kill.end(), [&](point_t p) {
            field.set(p.x, p.y, false);
        });

        for_each(to_revive.begin(), to_revive.end(), [&](point_t p) {
            field.set(p.x, p.y, true);
        });
    }

    field.print();

    return 0;
}
