#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <mutex>

#include <pthread.h>

#include <utils.hpp>
#include <game_field.hpp>

using namespace std;
using namespace utils;

struct job {
    game_field *current;
    game_field *next;
    int start;
    int end;
};

void* start_worker(void*);

mutex job_mutex;
mutex counter_mutex;

int counter;
queue<job*> job_queue;

bool is_running = true;

int main() {
    int number_of_generations = 100;
    string input_file = "input_file.txt";
    int number_of_threads = 19;

    game_field *field = new game_field(input_file);
    game_field *next;

    const int height = field->height();

    int step = ceil((float)height / number_of_threads);

    int actual_thread_number = height < number_of_threads ? height : number_of_threads;

    vector<pthread_t*> threads;

    for(int i = 0; i < actual_thread_number; i++) {
        threads.push_back(new pthread_t);

        pthread_create(threads.back(), NULL, start_worker, NULL);
    }

    for(int i = 0; i < number_of_generations; i++) {
        next = new game_field(*field);

        int tmp = height;
        int start_num = 0;
        int factor = -1;

        while(tmp > 0) {
            if(tmp <= step) {
                step = tmp;
                factor = 0;
            }

            job *j = new job;

            j->current = field;
            j->next = next;
            j->start = start_num;
            j->end = start_num + step;

            counter_mutex.lock();
            counter++;
            counter_mutex.unlock();

            job_mutex.lock();
            job_queue.push(j);
            job_mutex.unlock();

            tmp -= step;
            start_num += step;
        }

        while(counter != 0) {}

        delete field;
        field = next;
    }

    field->print();

    delete field;

    is_running = false;

    // delete threads
    for_each(threads.begin(), threads.end(), [](pthread_t *thread) {
        pthread_join(*thread, NULL);

        delete thread;
    });

    return 0;
}

void* start_worker(void *context) {
    while(is_running) {
        job *j = nullptr;

        // try to get a job
        job_mutex.lock();
        if(job_queue.size() > 0) {
            j = job_queue.front();
            job_queue.pop();
        }
        job_mutex.unlock();

        if(j != nullptr) {
            game_field *field = j->current;
            game_field *next = j->next;

            const int width = field->width();
            const int start = j->start;
            const int end = j->end;

            for(int y = start; y <= end; y++) {
                for(int x = 0; x < width; x++) {
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

            // job done
            delete j;

            counter_mutex.lock();
            counter--;
            counter_mutex.unlock();
        }
    }

    return nullptr;
}
