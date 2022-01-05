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

class MultipleIot {
 public:
   static MultipleIot* GetInstance();
   ~MultipleIot();

   std::unordered_map<std::string, pid_t> GetPids();

   void Start();
   void Runing();
   void Stop();

 private:
   MultipleIot();
   pid_t SpawnChild(std::string program, char** arg_list);
   void QiutProcess();

   static MultipleIot *instance_;
   std::atomic<int> child_pid_;
   std::unordered_map<std::string, pid_t> working_process_;
   std::thread check_thread_;
};
