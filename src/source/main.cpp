#include <iostream>
#include <string>
#include <utils.hpp>
#include <game_field.hpp>

using namespace std;
using namespace utils;

int main() {
    int number_of_generations = 1;
    string input_file = "input_file.txt";
    int number_of_threads = 1;

    game_field field(input_file);

    vector<point_t> points;

    for(int i = 0; i < number_of_generations; i++) {
        points.clear();

        for(int y = 0; y < field.height(); y++) {
            for(int x = 0; x < field.width(); x++) {
                point_t p;

                p.x = x;
                p.y = y;

                bool alive = field.get(p.x, p.y);
                int neighbors = field.neighbors(p.x, p.y);

                if(alive && neighbors < 2) {
                    p.state = false;
                    points.push_back(p);
                } else if(alive && neighbors > 3) {
                    p.state = false;
                    points.push_back(p);
                } else if(alive && (neighbors == 2 || neighbors == 3)) {
                    // do nothing
                } else if(!alive && neighbors == 3) {
                    p.state = true;
                    points.push_back(p);
                }
            }
        }

        for_each(points.begin(), points.end(), [&](point_t p) {
            field.set(p.x, p.y, p.state);
        });
    }

    field.print();

    return 0;
}
