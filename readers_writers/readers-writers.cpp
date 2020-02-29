#include <thread>
#include "shared_stream.h"
#include "semaphore.h"
#include "light_switch.h"

using namespace std;

myutil::shared_stream output_stream;
myutil::light_switch readSwitch;
myutil::semaphore roomEmpty(1);
myutil::semaphore turnstile(1);

void Reader(int id) {

    turnstile.wait();
    turnstile.signal();
    
    readSwitch.on(roomEmpty);
    output_stream.send("room has new reader... " + to_string(id));
    readSwitch.off(roomEmpty);

}

void Writer(int id) {

    turnstile.wait();
    roomEmpty.wait();
    output_stream.send("room is now empty...");
    output_stream.send("room has new writer... " + to_string(id));
    output_stream.send("room is now empty...");
    turnstile.signal();
    roomEmpty.signal();

}

int main() {

    int const TOTAL_THREADS = 12;
    thread threads[TOTAL_THREADS];

    for (int id = 0; id < TOTAL_THREADS; id++) {

        if (id % 3 == 0) { threads[id] = thread(Writer, id); }
        else { threads[id] = thread(Reader, id); }

    }

    for (auto& th : threads) { th.join(); }

    return 0;
}

