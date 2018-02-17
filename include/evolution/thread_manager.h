/** @file thread_manager.h
 *  @brief The manager starts/accesses the individual threads.
 *
 *  It is used as the central access point.
 */
#ifndef MANAGER_H
#define MANAGER_H

#define MAX_THREADS 10

#include <thread>


namespace evolution {
   class ThreadManager {
   public:
      ThreadManager();
      ~ThreadManager();
      void StartThread(Thread *t_thread);
      void AddThread(Thread *t_thread);
      Thread *GetThread(int t_thread_id);
      void Wait(void);
   private:
      Thread *m_thread[MAX_THREADS];
      std::thread m_std_sthread[MAX_THREADS];
      int m_number_of_threads;
   };
}

#endif

