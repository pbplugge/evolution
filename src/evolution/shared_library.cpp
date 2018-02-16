#include "../../include/evolution.h"
#include <cstring>

using namespace evolution;

/**
 * A global.
 * Its the only way to run as a shared library and remember between calls.
 */
ThreadManager *thread_manager;


/**
 * Creates the manager, must be called before starting a simulation.
 */
extern "C" void init(void) {
   // Init random numbers so each run is different.
   srand (time(NULL));

   // Create the global thread manager.
	thread_manager = new ThreadManager();
}

/**
 * Delete the thread manager.
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
   Thread *g = thread_manager->GetThread(t_thread);

   if (!g) return 0;

   switch (t_variable) {
   case 0:
      return g->GetPopulation()->GetGeneration();
      break;
   case 1:
      return g->GetPopulation()->GetNumberOfActiveMembers();
      break;
   }

   //
   return 0;
}

/**
 * Sets requested values in an array.
 * Possible values:
 * 0 => Average fitness in population per generation.
 * 1 => Maximum fitness in population per generation.
 * 2 => Average number of components used
 * 3 => Maximum number of components used.
 * 4 => Total components used.
 * 5 => Population size
 * TODO: => Calculation time per generation.
 */
extern "C" double *get_stats(int t_thread,int t_variable) {
   Thread *g = thread_manager->GetThread(t_thread);

   if (!g) return 0;

   Statistics *stats = 0;

   switch (t_variable) {
   case 0:
      stats = g->GetPopulation()->GetStatsAvgFitness();
      break;
   case 1:
      stats = g->GetPopulation()->GetStatsMaxFitness();
      break;
   case 2:
      stats = g->GetPopulation()->GetStatsAvgComponentsUsed();
      break;
   case 3:
      stats = g->GetPopulation()->GetStatsMaxComponentsUsed();
      break;
   case 4:
      stats = g->GetPopulation()->GetStatsTotalComponentsUsed();
      break;
   case 5:
      stats = g->GetPopulation()->GetStatsPopulationSize();
      break;
   }

   if (stats) {
      double *f = (double*) malloc ( sizeof(double) * stats->GetLength());

      for (int t=0; t<stats->GetLength(); t++) {
         f[t] = stats->GetValue(t);
      }
      return f;
   }
   return 0;
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
