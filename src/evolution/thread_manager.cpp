
#include "../../include/evolution.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <stdbool.h>
#include <thread>

using namespace evolution;


ThreadManager::ThreadManager() {
   m_number_of_threads = 0;
   for (int t=0;t<MAX_THREADS; t++)
      m_thread[t] = 0;
}

ThreadManager::~ThreadManager() {
   for (int t=0; t<m_number_of_threads; t++) {
      m_thread[t]->Stop();
   }
}


void runthread(Thread *t_thread) {
   t_thread->Start();
}

/*
 * Start one evolution thread.
 */
void ThreadManager::StartThread(Thread *t_thread) {
   if (m_number_of_threads == MAX_THREADS - 1) {
      std::cout << "ThreadManager::StartThread() -> Error: maximum number of threads reached.\n";
      return;
   }

   std::cout << "ThreadManager::StartThread()\n";
   m_thread[m_number_of_threads] = t_thread;
   m_number_of_threads ++;
   std::thread t(runthread, t_thread);
   t.join();
}

/**
 * Add thread without running.
 */
void ThreadManager::AddThread(Thread *t_thread) {
   if (m_number_of_threads == MAX_THREADS - 1) {
      std::cout << "ThreadManager::AddThread() -> Error: maximum number of threads reached.\n";
      return;
   }

   m_thread[m_number_of_threads] = t_thread;
   m_number_of_threads ++;
}

/**
 * Get thread
 */
Thread *ThreadManager::GetThread(int t_thread_id) {
   return m_thread[t_thread_id];
}
