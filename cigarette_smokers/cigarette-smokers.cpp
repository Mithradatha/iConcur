#include <thread>
#include <mutex>
#include "shared_stream.h"
#include "semaphore.h"

using namespace std;

myutil::shared_stream output_stream;

mutex ingredientTable;
bool tobacco_available, paper_available, match_available = false;

myutil::semaphore agentNeeded(1);

myutil::semaphore tobaccoSupplied(0);
myutil::semaphore paperSupplied(0);
myutil::semaphore matchSupplied(0);

myutil::semaphore tobaccoSmoker(0);
myutil::semaphore paperSmoker(0);
myutil::semaphore matchSmoker(0);

void TobaccoPaperAgent() {

    agentNeeded.wait();
    output_stream.send("agent placing tobacco on the table...");
    tobaccoSupplied.signal();
    output_stream.send("agent placing paper on the table...");
    paperSupplied.signal();

}

void PaperMatchAgent() {

    agentNeeded.wait();
    output_stream.send("agent placing paper on the table...");
    paperSupplied.signal();
    output_stream.send("agent placing match on the table...");
    matchSupplied.signal();

}

void MatchTobaccoAgent() {

    agentNeeded.wait();
    output_stream.send("agent placing match on the table...");
    matchSupplied.signal();
    output_stream.send("agent placing tobacco on the table...");
    tobaccoSupplied.signal();

}

void TobaccoPusher() {

    tobaccoSupplied.wait();
    ingredientTable.lock();
    if (paper_available) {
        paper_available = false;
        output_stream.send("pusher removed tobacco and paper from the table...");
        matchSmoker.signal();
    } else if (match_available) {
        match_available = false;
        output_stream.send("pusher removed tobacco and match from the table...");
        paperSmoker.signal();
    } else {
        tobacco_available = true;
    }
    ingredientTable.unlock();

}

void PaperPusher() {

    paperSupplied.wait();
    ingredientTable.lock();
    if (tobacco_available) {
        tobacco_available = false;
        output_stream.send("pusher removed paper and tobacco from the table...");
        matchSmoker.signal();
    } else if (match_available) {
        match_available = false;
        output_stream.send("pusher removed paper and match from the table...");
        tobaccoSmoker.signal();
    } else {
        paper_available = true;
    }
    ingredientTable.unlock();

}

void MatchPusher() {

    matchSupplied.wait();
    ingredientTable.lock();
    if (paper_available) {
        paper_available = false;
        output_stream.send("pusher removed match and paper from the table...");
        tobaccoSmoker.signal();
    } else if (tobacco_available) {
        tobacco_available = false;
        output_stream.send("pusher removed match and tobacco from the table...");
        paperSmoker.signal();
    } else {
        match_available = true;
    }
    ingredientTable.unlock();

}

void TobaccoSmoker() {

    tobaccoSmoker.wait();
    output_stream.send("paper and match delivered to smoker...");
    output_stream.send("smoker with tobacco smoking...");
    agentNeeded.signal();

}

void PaperSmoker() {

    paperSmoker.wait();
    output_stream.send("match and tobacco delivered to smoker...");
    output_stream.send("smoker with paper smoking...");
    agentNeeded.signal();

}

void MatchSmoker() {

    matchSmoker.wait();
    output_stream.send("tobacco and paper delivered to smoker...");
    output_stream.send("smoker with match smoking...");
    agentNeeded.signal();

}

/* TODO: Randomize the agents */

int main() {

    /* Multiples of 3 to complete all threads */

    int SMOKERS = 3;

    int THREAD_COUNT = 4 * SMOKERS;
    thread threads[THREAD_COUNT];

    threads[0] = thread(TobaccoSmoker);
    threads[1] = thread(PaperSmoker);
    threads[2] = thread(MatchSmoker);

    threads[3] = thread(TobaccoPusher);
    threads[4] = thread(TobaccoPusher);
    threads[5] = thread(PaperPusher);
    threads[6] = thread(PaperPusher);
    threads[7] = thread(MatchPusher);
    threads[8] = thread(MatchPusher);

    threads[9] = thread(TobaccoPaperAgent);
    threads[10] = thread(PaperMatchAgent);
    threads[11] = thread(MatchTobaccoAgent); 

    for (auto& th : threads) { th.join(); }

    return 0;
}
