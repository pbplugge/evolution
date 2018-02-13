#ifndef MANAGER_H
#define MANAGER_H

#define MAX_THREADS 10


/**
 * The manager starts the individual threads.
 */
namespace evolution {
   class ThreadManager {
   public:
      ThreadManager();
      ~ThreadManager();
      void StartThread(Thread *t_thread);
      void AddThread(Thread *t_thread);
      Thread *GetThread(int t_thread_id);

   private:
      Thread *m_thread[MAX_THREADS];
      int m_number_of_threads;
   };
}

#endif

