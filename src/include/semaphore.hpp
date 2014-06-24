#ifndef __SEMAPHORE_HPP__
#define __SEMAPHORE_HPP__

#include <mutex>

class semaphore {
public:
    semaphore();
    semaphore(unsigned int);

    void wait();
    void increment();
    void decrement();

private:
    unsigned int counter;
    std::mutex mtx;
};

#endif
