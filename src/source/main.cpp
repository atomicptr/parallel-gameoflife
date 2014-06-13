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

    field.set(2, 2, true);
    field.set(3, 3, true);
    field.set(1, 1, true);
    field.set(0, 0, true);

    cout << field.neighbors(2, 2) << endl;

    field.print();

    return 0;
}
