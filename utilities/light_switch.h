#ifndef __LIGHT_SWITCH_H__
#define __LIGHT_SWITCH_H__

#include <mutex>
#include "semaphore.h"

namespace myutil {

class light_switch {

    int count;
    std::mutex mtx;

public:
    light_switch();

    void on(semaphore&);

    void off(semaphore&);
};

}

#endif
