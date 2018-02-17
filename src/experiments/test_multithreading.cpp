/** @file multithreading.cpp
 *  @brief A test to see if multi-threading works.
 *
 *  Creates two threads, both outputting theit own random number to standard output.
 *  Both outputs should appear
 */
#include "../../include/evolution.h"
#include <chrono>
#include <thread>

using namespace evolution;

extern ThreadManager *thread_manager;



// Create component type for adding.
class ComponentTypeDummy:public ComponentType {
public:
   ComponentTypeDummy() {
      m_number_of_inputs = 0;
      m_number_of_outputs = 0;
      m_number_of_parameters = 0;
      m_name = "dummy";
      m_max_number_of_components = 1;
      m_req_number_of_components = 1;
   }

   void Execute(Component *t_component) {
   }
};


class MultiThreadingTestThread: public evolution::Thread {
public:
   ~MultiThreadingTestThread(){
   }

   void Init(void) {
      GetConfig()->SetMinimumPopulationSize(1);
      GetConfig()->SetMaximumPopulationSize(5);

      AddComponentType(new ComponentTypeDummy());

      m_random_number = rand();
   }

   void CalculateFitness(evolution::Individual *t_individual) {
   }

   bool ContinueEvolution(void){
      std::cout << "random number: " << m_random_number << "\n";

      std::this_thread::sleep_for (std::chrono::seconds(1));

      if (m_population.GetGeneration() == 3)
         return false;
      return true;
   }
private:
   int m_random_number;
};



extern "C" void experiment_multithreading(void) {
   init();

   MultiThreadingTestThread *thread1 = new MultiThreadingTestThread();
   MultiThreadingTestThread *thread2 = new MultiThreadingTestThread();

   thread_manager->StartThread(thread1);
   thread_manager->StartThread(thread2);

   thread_manager->Wait();
}




