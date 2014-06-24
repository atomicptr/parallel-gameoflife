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

void semaphore::increment() {
    mtx.lock();
    this->counter++;
    mtx.unlock();
}

void semaphore::decrement() {
    mtx.lock();
    this->counter--;
    mtx.unlock();
}
