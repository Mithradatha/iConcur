#ifndef  __SEMAPHORE_H__
#define  __SEMAPHORE_H__

#include <mutex>
#include <condition_variable>

namespace myutil {

class semaphore {

    int count;
    std::mutex mtx;
    std::condition_variable cv;

public:
    semaphore();
    semaphore(int);
    void wait();
    void signal();
};

}

#endif
