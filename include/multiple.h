#pragma once

#include <unistd.h>
#include <vector>
#include <iostream>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <atomic>
#include <unordered_map>
#include <thread>

#define TESTFORK MultipleIot::GetInstance()

struct ProcInfo {
    pid_t pid = 0;        //记录pid
    uint32_t count = 5;   //默认5次
};

class MultipleIot {
 public:
   static MultipleIot* GetInstance();
   ~MultipleIot();

   void Start();
   void Runing();
   void Stop();

 private:
   MultipleIot();
   pid_t SpawnChild(std::string program, char** arg_list);
   void QiutProcess();

   static MultipleIot *instance_;
   std::atomic<pid_t> child_pid_;
   std::unordered_map<std::string, ProcInfo> working_process_;
   std::thread check_thread_;
};
