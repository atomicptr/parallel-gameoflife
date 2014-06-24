#include <semaphore.hpp>

semaphore::semaphore() {
    this->counter = 0;
}

semaphore::semaphore(unsigned int start_value) {
    this->counter = start_value;
}

void semaphore::wait() {
    while(this->counter != 0) {
    }
}

void semaphore::acquire() {
    mtx.lock();
    this->counter++;
    mtx.unlock();
}

void semaphore::free() {
    mtx.lock();
    this->counter--;
    mtx.unlock();
}
