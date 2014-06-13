#include <iostream>
#include <string>
#include <utils.hpp>
#include <game_field.hpp>

using namespace std;

int main() {
    int number_of_generations = 5;
    string input_file = "input_file.txt";
    string output_file = "output_file.txt";
    int number_of_threads = 1;

    game_field field(input_file);

    field.set(0, 0, true);
    field.set(4, 4, true);

    field.print();

    return 0;
}
