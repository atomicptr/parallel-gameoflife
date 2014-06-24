#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <mutex>
#include <chrono>

#include <pthread.h>

#include <utils.hpp>
#include <game_field.hpp>
#include <semaphore.hpp>

using namespace std;
using namespace utils;

struct job {
    game_field *current;
    game_field *next;
    int start;
    int end;
};

void* start_worker(void*);
float get_average(vector<float>);

mutex job_mutex;
mutex counter_mutex;
mutex cell_time_mutex;

semaphore sema;
queue<job*> job_queue;

vector<float> time_per_cell;

bool is_running = true;

int main() {
    // start parameters
    int number_of_generations = 100;
    string input_file = "input_file.txt";
    int number_of_threads = 19;

    chrono::time_point<chrono::system_clock> start_time = chrono::system_clock::now();

    // create fields
    game_field *field = new game_field(input_file);
    game_field *next;

    const int height = field->height();

    int step = ceil((float)height / number_of_threads);

    int actual_thread_number = height < number_of_threads ? height : number_of_threads;

    vector<pthread_t*> threads;

    // start threads
    for(int i = 0; i < actual_thread_number; i++) {
        threads.push_back(new pthread_t);

        pthread_create(threads.back(), NULL, start_worker, NULL);
    }

    vector<float> time_per_generation;
    chrono::time_point<chrono::system_clock> generation_start_time;

    // calc generations
    for(int i = 0; i < number_of_generations; i++) {
        // get start time
        generation_start_time = chrono::system_clock::now();

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

            sema.increment();

            job_mutex.lock();
            job_queue.push(j);
            job_mutex.unlock();

            tmp -= step;
            start_num += step;
        }

        // wait for threads to complete all jobs
        sema.wait();

        delete field;
        field = next;

        // calculate ms this generation took
        chrono::duration<float> generation_elapsed_seconds = chrono::system_clock::now() - generation_start_time;

        time_per_generation.push_back(generation_elapsed_seconds.count() * 1000);
    }

    // print final field
    field->print();

    delete field;

    // calc execution time
    chrono::duration<float> elapsed_time_s = chrono::system_clock::now() - start_time;

    float generations_per_second = time_per_generation.size() / elapsed_time_s.count();
    float cells_per_second = time_per_cell.size() / elapsed_time_s.count();

    cout << "avg. time per generation: " << get_average(time_per_generation) << "ms" << endl;

    cout << "avg. time per cell: " << get_average(time_per_cell) << "ms" << endl;

    cout << "generations per second: " << generations_per_second << endl;

    cout << "cells per second: " << cells_per_second << endl;

    cout << "total execution time: " << elapsed_time_s.count() * 1000 << "ms" << endl;

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
            chrono::time_point<chrono::system_clock> cell_start_time = chrono::system_clock::now();

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

            // job is done, yay
            delete j;

            sema.decrement();

            // calculate ms this generation took
            chrono::duration<float> cell_elapsed_seconds = chrono::system_clock::now() - cell_start_time;

            cell_time_mutex.lock();
            time_per_cell.push_back(cell_elapsed_seconds.count() * 1000);
            cell_time_mutex.unlock();
        }
    }

    return nullptr;
}

float get_average(vector<float> v) {
    float avg = 0.0;

    for_each(v.begin(), v.end(), [&](float f) {
        avg += f;
    });

    return avg / v.size();
}
