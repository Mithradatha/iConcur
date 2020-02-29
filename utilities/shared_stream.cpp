#include "shared_stream.h"

using namespace myutil;

shared_stream::shared_stream() {}

void shared_stream::send(std::string str) {

    mtx.lock();
    std::cout << str << std::endl;
    mtx.unlock();

}
