#include <iostream>
#include "../../include/evolution.h"


using namespace evolution;

/**
 * Family constructor.
 */
Thread::Thread() {
   std::cout << "Thread::Thread()\n";
   m_stop = false;
}

/**
 * Destructor.
 */
Thread::~Thread() {
}

/**
 * Start generator.
 */
void Thread::Start(void) {
   int t;

   std::cout << "Thread::Start()";

   if (m_component_library.GetNumberOfComponentTypes() == 0) {
      // Virtual function.
      Init();
   }

   if (!m_population.GetNumberOfActiveMembers()) {
      m_population.CreatePopulation(m_config.GetMinimumPopulationSize(),m_config.GetMaximumPopulationSize(),&m_component_library);
   }

   while (!m_stop) {
      // Method one:
      // - mutations are done on the existing population.
      // - Weaker individuals have a higher chance of getting mutated.
      if (false) {
         // 1) Do operations on the population.
         m_population.MutateStructures(m_config.GetStructureMutationChance());
         m_population.MutateParameters(m_config.GetParameterMutationChance());
         m_population.DoCrossOver(m_config.GetCrossoverChance());

         // Calculate the fitness of each individual that is marked as dirty.
         for (t=0; t<m_population.GetNumberOfActiveMembers(); t++) {
            if (m_population.GetIndividual(t)->Dirty()) {
               m_population.GetIndividual(t)->ClearDirty();
               CalculateFitness(m_population.GetIndividual(t));
            }
         }
         // Resort the population on fitness.
         m_population.SortOnFitness();

         // Remove some from the population.
         m_population.RemoveWeakestFromPopulation();
      }

      // Method two, my variant on APGA: http://www.cs.vu.nl/~gusz/papers/PPSN2004-Eiben-Marchiori-Valko.pdf
      // - An existing (minimum) population produces offspring when other individuals die from old age. A bit weird but thats how it goes.
      // - Individuals with better fitness live longer.
      // - If improvement on average fitness or best fitness, reduce population size with 1. Else increase population size with 1.
      // Not the complete population needs to be simulated each generation, only on birth.
      if (true) {
         // Change population size depending on average and best fitness.
         if (m_population.GetGeneration() > 1) {
            // Determine if the population needs to grow or shrink.
            t = m_population.GetGeneration();
            if (m_population.GetStatsAvgFitness()->GetValue(t-1) > m_population.GetStatsAvgFitness()->GetValue(t-2) ||
                m_population.GetStatsMaxFitness()->GetValue(t-1) > m_population.GetStatsMaxFitness()->GetValue(t-2) ) {
               // Decrease population size if minimum is not reached.
               if (m_population.GetNumberOfActiveMembers() > m_config.GetMinimumPopulationSize()) {
                  m_population.SetNumberOfActiveMembers(m_population.GetNumberOfActiveMembers() - 1);
               }
            } else if (m_population.GetNumberOfActiveMembers() < m_config.GetMaximumPopulationSize()) {
               t = m_population.GetNumberOfActiveMembers();
               m_population.SetNumberOfActiveMembers(m_population.GetNumberOfActiveMembers() + 1);

               // make sure the new member is sorted.
               m_population.GetIndividual(t)->SetAge(100);
               m_population.RepositionIndividualOnFitness(t);
            }
         }

         // Reduce age depending on its ranking.
         // TODO: make speed of aging & target age configurable.
         for (t=0; t<m_population.GetNumberOfActiveMembers(); t++) {
            double age = m_population.GetIndividual(t)->GetAge();
            double aging = 1.0f - m_population.GetIndividual(t)->GetAverageFitness();

            std::cout << "individual " << t << " ages with " << aging << "\n";

            age -= aging;
            m_population.GetIndividual(t)->SetAge(age);

            // If it dies from old age, replace by a offspring.
            if (age < 0) {
               m_population.GetIndividual(t)->Die();
               m_population.CreateIndividualFromCrossOver(t);
               m_population.GetIndividual(t)->SetAge(10);
            }
         }


      }


      // Save the best in hall of fame.
      m_population.UpdateHallOfFame();

      m_population.UpdateStatistics();
      //if (m_population.GetGeneration() == 5)      exit(1);

      m_population.IncreaseGeneration();
   }

   // Set stop to false again so we could start again if we want.
   m_stop = false;
}

/**
 * Stop the generator.
 */
void Thread::Stop(void) {
   m_stop = true;
}


void Thread::AddComponentType(ComponentType *t_component_type) {
   m_component_library.AddComponentType(t_component_type);
}
