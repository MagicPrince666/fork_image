#include <iostream>

#include "interface.h"
#include "multiple.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"  // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h" // support for user defined types

int main(int argc, char* argv[])
{
    spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    spdlog::info("Test multiple fork!");

    TESTFORK->Start();
    TESTFORK->Runing();
    TESTFORK->Stop();
    return 0;
}
