#ifndef __SHARED_STREAM_H__
#define __SHARED_STREAM_H__

#include <mutex>
#include <iostream>
#include <string>

namespace myutil {

class shared_stream {

    std::mutex mtx;

/* TODO: pass ostream& to constructor */

public:
    shared_stream();

    void send(std::string);

};

}

#endif
