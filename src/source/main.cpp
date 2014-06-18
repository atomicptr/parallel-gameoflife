#include <iostream>
#include <string>
#include <cmath>

#include <pthread.h>
#include <semaphore.h>

#include <utils.hpp>
#include <game_field.hpp>

using namespace std;
using namespace utils;

struct thread_params {
    game_field *current;
    game_field *next;
    int start;
    int end;
    sem_t *semaphore;
};

void* do_step(void*);

sem_t *semaphore;
string sema_name = "semaphore-parallel-gol-123456";

int main() {
    int number_of_generations = 1;
    string input_file = "input_file.txt";
    int number_of_threads = 19;

    game_field *field = new game_field(input_file);
    game_field *next;

    const int height = field->height();

    int step = ceil((float)height / number_of_threads);

    int actual_thread_number = height < number_of_threads ? height : number_of_threads;

    semaphore = sem_open(sema_name.c_str(), O_CREAT, 0644, actual_thread_number);

    if(semaphore == SEM_FAILED) {
        cerr << "ERR: Couldn't create semaphore" << endl;
        exit(1);
    }

    vector<thread_params> params;

    for(int i = 0; i < number_of_generations; i++) {
        next = new game_field(field);

        int tmp = height;
        int start_num = 0;
        int factor = -1;

        while(tmp > 0) {
            if(tmp <= step) {
                step = tmp;
                factor = 0;
            }

            sem_wait(semaphore);

            thread_params parameter;

            parameter.current = field;
            parameter.next = next;
            parameter.start = start_num;
            parameter.end = start_num + step + factor;
            parameter.semaphore = semaphore;

            params.push_back(parameter);

            pthread_t thread;

            pthread_create(&thread, NULL, do_step, &params.back());

            tmp -= step;
            start_num += step;
        }

        for(int j = 0; j < actual_thread_number; j++) {
            sem_wait(semaphore);
        }

        delete field;
        field = next;
    }

    field->print();

    delete field;

    sem_close(semaphore);
    sem_unlink(sema_name.c_str());

    return 0;
}

void* do_step(void *context) {
    struct thread_params *params = static_cast<thread_params*>(context);

    game_field *field = params->current;
    game_field *next = params->next;

    for(int y = params->start; y <= params->end; y++) {
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

    sem_post(params->semaphore);

    return nullptr;
}
