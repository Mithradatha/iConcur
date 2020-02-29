#include <iostream>
#include <thread>
#include "shared_stream.h"
#include "semaphore.h"

using namespace std;

myutil::shared_stream output_stream;
myutil::semaphore aArrived(0);
myutil::semaphore bArrived(0);

void A() {
  
    output_stream.send("Statemnt A1");
    aArrived.signal();
    bArrived.wait();
    output_stream.send("Statement A2");

}

void B() {

    output_stream.send("Statement B1");
    bArrived.signal();
    aArrived.wait();
    output_stream.send("Statement B2");

}

int main() {
    thread a(A);
    thread b(B);
    a.join();
    b.join();

    return 0;
}

