#include "semaphore.h"

using namespace myutil;

semaphore::semaphore() : semaphore::semaphore(1) {}
semaphore::semaphore(int _count) : count(_count) {}

void semaphore::wait() {
    std::unique_lock<std::mutex> lck(mtx);
    while(count == 0) { cv.wait(lck); }
    count --;
}

void semaphore::signal() {
    std::unique_lock<std::mutex> lck(mtx);
    count++;
    cv.notify_one();
}
