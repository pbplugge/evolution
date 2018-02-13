#include "../../include/evolution.h"
#include <cstring>

using namespace evolution;


ThreadManager *thread_manager;


/**
 * Creates the manager, must be called before starting a simulation.
 */
extern "C" void init(void) {
	thread_manager = new ThreadManager();

	//thread_manager->CreateThreads(number_of_threads);
}

/**
 *
 */
extern "C" void cleanup(void) {
   delete thread_manager;
}

/**
 * Starts the threads.
 */
//extern "C" void start_generators(void) {
   //thread_manager->StartThreads();
//}

/**
 * Possible variable values:
 * 0 => population size.
 * 1 => Maximum number of generations.
 */
extern "C" void set_int(int t_thread, int t_variable, int t_value) {
   /*
   Thread *g = thread_manager->GetThread(t_thread);

   if (!g) return;

   switch (t_variable) {
   case 0:
      g->GetConfig()->SetPopulationSize(t_value);
      break;
   case 1:
      g->GetConfig()->SetMaximumGenerations(t_value);
      break;
   }
   */
}

/**
 * Get information in integer format.
 * Possible values:
 * 0 => Current generation.
 * 1 => members in population.
 * 2 => Number of threads active.
 */
extern "C" int get_int(int t_thread, int t_variable) {
   //EvolutionThread *g = thread_manager->GetThread(t_thread);

   //return g->GetPopulation()->GetGeneration();
}

/**
 * Sets requested values in an array.
 * Possible values:
 * 0 => Average population fitness per generation.
 * 1 => Maximum fitness in population per generation.
 * 2 => Calculation time per generation.
 */
extern "C" void get_double_array(int t_thread,int t_variable, double *t_values, int t_len) {

}

/**
 * Returns requested info as a sting.
 * variable values:
 * 0 => version.
 * 1 => available functions.
 * 2 => Status summary.
 * 3 => available price data.
 */
extern "C" char* get_info(int t_thread, int t_variable) {
   return (char*)"test";
}

/**
 * Add a primitive to the evolution.
 */
extern "C" void add_primitive(int t_thread, char *t_p) {
   //thread_manager->GetThread(thread)->GetConfig()->AddPrimitive(t_p);
}

/**
 * Add a terminal to the evolution.
 *
 */
extern "C" void add_terminal(int t_thread, char *t_p,int t_constant) {
   //thread_manager->GetThread(t_thread)->GetConfig()->AddTerminal(t_p,t_constant);
}

/**
 * Return json of an individual so we can plot it in networkx.
 */
extern "C" char *get_individual_json(int t_thread, int t_individual) {
   if (!thread_manager)      return (char*)"{\"error\":\"no thread_manager\"}";
   if (!thread_manager->GetThread(t_thread))   return (char*)"{\"error\":\"This thread does not exist\"}";

   std::string jsonstr = thread_manager->GetThread(t_thread)->GetPopulation()->GetIndividual(t_individual)->GetEvolutionaryProgram()->ToJson();
   char *json = (char*) malloc ( jsonstr.length() );
   strcpy( json , jsonstr.c_str());

   return json;
}
