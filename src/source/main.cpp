#include <iostream>
#include <string>

#include <pthread.h>

#include <utils.hpp>
#include <game_field.hpp>

using namespace std;
using namespace utils;

struct thread_params {
    game_field *current;
    game_field *next;
    int start;
    int end;
};

pthread_mutex_t mtx;

void* do_step(void*);//game_field*, game_field*, int, int);

int main() {
    int number_of_generations = 1;
    string input_file = "input_file.txt";
    int number_of_threads = 1;

    game_field *field = new game_field(input_file);
    game_field *next;

    vector<pthread_mutex_t> mutex;

    int height = field->height();

    for(int i = 0; i < number_of_generations; i++) {
        next = new game_field(field);

        // TODO: create threads
        struct thread_params params;

        params.current = field;
        params.next = next;
        params.start = 0;
        params.end = height;

        pthread_t thread;

        pthread_mutex_lock(&mtx);
        pthread_create(&thread, NULL, do_step, &params);
        // END TODO: create threads

        pthread_mutex_lock(&mtx);
        delete field;
        field = next;
        pthread_mutex_unlock(&mtx);
    }

    field->print();

    delete field;

    return 0;
}

void* do_step(void *context) {
    struct thread_params *params = static_cast<thread_params*>(context);

    game_field *field = params->current;
    game_field *next = params->next;

    for(int y = params->start; y < params->end; y++) {
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

    pthread_mutex_unlock(&mtx);
}
