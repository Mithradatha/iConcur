#include "light_switch.h"

using namespace myutil;

light_switch::light_switch() {}

void light_switch::on(semaphore& sem) {

    mtx.lock();
    count++;
    if (count == 1) { sem.wait(); }
    mtx.unlock();

}

void light_switch::off(semaphore& sem) {

    mtx.lock();
    count--;
    if (count == 0) { sem.signal(); }
    mtx.unlock();

}
