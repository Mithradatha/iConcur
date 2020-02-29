#include <thread>
#include "semaphore.h"
#include "shared_stream.h"

using namespace std;

int const NUM_FORKS = 10;

myutil::shared_stream output_stream;
myutil::semaphore forks[NUM_FORKS];
myutil::semaphore seatOpen(NUM_FORKS - 1);

int left(int i) { return i; }

int right(int i) { return (i + 1) % NUM_FORKS; }

void pickup_forks(int i) {

    seatOpen.wait();
    forks[ right(i) ].wait();
    forks[  left(i) ].wait();

}

void drop_forks(int i) {

    forks[ right(i) ].signal();
    forks[  left(i) ].signal();
    seatOpen.signal();

}

void Philosopher(int id) {

    output_stream.send("philosopher " + to_string(id) + " thinking...");
    pickup_forks(id);
    output_stream.send("philosopher " + to_string(id) + " eating...");
    drop_forks(id);

}

int main() {

    thread philosophers[NUM_FORKS];

    for(int id = 0; id < NUM_FORKS; id++) {
        philosophers[id] = thread(Philosopher, id);
    }

    for(auto& th : philosophers) { th.join(); }

}
