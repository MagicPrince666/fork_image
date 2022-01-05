#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include "multiple.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"  // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h" // support for user defined types

std::vector<std::string> iots = {"hello", "hi"};

MultipleIot* MultipleIot::instance_ = nullptr;

MultipleIot::MultipleIot () {
    working_process_.clear();
    check_thread_ = std::thread([](MultipleIot* pThis){
        pThis->QiutProcess();
    }, this);
}

MultipleIot::~MultipleIot () {
    if (check_thread_.joinable()) {
        check_thread_.join();
	}
    for (std::unordered_map<std::string, pid_t>::iterator iter = working_process_.begin(); iter != working_process_.end(); iter++) {
        spdlog::info("program {} pid {}", iter->first, iter->second);
        // 清場收工
        kill(iter->second, SIGTERM);
    }
}

MultipleIot *MultipleIot::GetInstance() {
    if (!instance_) {
        instance_ = new MultipleIot();
    }
    return instance_;
}

void MultipleIot::QiutProcess() {
    char *arg_list[] = {nullptr, nullptr};
    while(1) {
        // 每隔一段時間檢查一次進程
        for (std::unordered_map<std::string, pid_t>::iterator iter = working_process_.begin(); iter != working_process_.end(); iter++) {
            spdlog::info("program {} pid {}", iter->first, iter->second);
            // kill(iter->first, SIGTERM);
            std::string process_exists = "/proc/" + std::to_string(iter->second);
            if (-1 == access(process_exists.c_str(), F_OK)) {
                spdlog::error("Process {} quit!", iter->first);
                // 檢查pid不在運行
                pid_t tmp_pid = SpawnChild(iter->first, arg_list);
                if(tmp_pid > 0) {
                    spdlog::info("Process {} restart!", iter->first);
                    // 更新pid
                    working_process_[iter->first] = tmp_pid;
                }
                // working_process_.erase(iter->first);
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

pid_t MultipleIot::SpawnChild(std::string program, char** arg_list)
{
    pid_t ch_pid = fork();
    if (ch_pid == -1) {
        spdlog::error("fork err = {} {}!", errno, strerror(errno));
        exit(EXIT_FAILURE);
    } else if (ch_pid > 0) {
        spdlog::info("spawn child with pid - {}", ch_pid);
        return ch_pid;
    } else {
        int ret = execve(program.c_str(), arg_list, nullptr);
        if(ret == -1) {
            spdlog::error("execl err = {} {}!", errno, strerror(errno));
        }
        // exit(EXIT_FAILURE);
    }
}

void MultipleIot::Start() {
    spdlog::info("!!!!!!!!!!!!!Start fork test!!!!!!!!!!!!");
}

std::unordered_map<std::string, pid_t> MultipleIot::GetPids() {
    return working_process_;
}

void MultipleIot::Runing() {
    char *arg_list[] = {nullptr, nullptr};
    for (std::string itvec : iots) {
        if (-1 == access(itvec.c_str(), F_OK)) {
            spdlog::error("Program file {} does not exist in current directory!", itvec.c_str());
        } else {
            pid_t tmp_pid = SpawnChild(itvec, arg_list);
            if(tmp_pid > 0) {
                working_process_[itvec] = tmp_pid;
            }
        }
    }

    while ((child_pid_ = wait(nullptr)) > 0) {
        spdlog::info("Program pid {} terminated", child_pid_);
    }
}

void MultipleIot::Stop() {
    spdlog::info("!!!!!!!!!!!!! End fork test !!!!!!!!!!!!");
}
