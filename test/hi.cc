#include <iostream>
#include <chrono>
#include <thread>

#include "interface.h"

int main(int argc, char* argv[])
{
    std::cout << BLUE << "test fork 2" << std::endl;

    while(1) {
        std::cout << BLUE << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return 0;
}
