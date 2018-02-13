#ifndef POPULATION_H
#define POPULATION_H

#include "component_manager.h"
#include "statistics.h"

namespace evolution {
   class Individual;
   class HallOfFame;

   /**
    * Population of individuals.
    * The individuals are always sorted by fitness descending.
    * Whenever one gets created or mutated, the fitness is recalculated and put on its new spot.
    * It features statistics and hall of fame out of the box.
    */
   class Population {
   public:
      Population();
      ~Population();
      void CreatePopulation(int t_minimum_number_of_active_members,int t_maximum_number_of_numbers, ComponentLibrary *t_component_library);

      // Some getters.
      Individual *GetIndividual(int t);
      Individual *GetRandomParent(void);
      int GetGeneration(void);
      int GetNumberOfActiveMembers(void);
      void SetNumberOfActiveMembers(int t_number_of_active_members);

      // Functions to change the population.
      void MutateStructures(double t_mutate_chance);
      void MutateParameters(double t_mutate_chance);
      void DoCrossOver(double t_crossover_chance);
      void RemoveWeakestFromPopulation(void);
      void SortOnFitness(void);
      void CreateRandomIndividual(void);
      void UpdateHallOfFame(void);
      void IncreaseGeneration(void);
      void UpdateStatistics(void);
      void RepositionIndividualOnFitness(int t_index);
      double GetIndividualTriangularNumber(int t_index);
      void CreateIndividualFromCrossOver(int t_index);

      Statistics *GetStatsAvgFitness(void);
      Statistics *GetStatsMaxFitness(void);
      Statistics *GetStatsAvgComponentsUsed(void);
      Statistics *GetStatsMaxComponentsUsed(void);
      Statistics *GetStatsPopulationSize(void);
      Statistics *GetStatsTotalComponentsUsed(void);

      // TODO:
      // void AddToPopulation(Individual *b);

      // TODO:
      // Prevent double individuals.

      // TODO: statistics over time: avg fitness, max fitness, avg components used, max components used.

   private:
      // The object that manages the components to optimize speed and memory use.
      ComponentManager m_component_manager;

      int m_maximum_number_of_numbers;
      int m_number_of_active_members;
      int m_minimum_number_of_active_members;

      Individual **m_individual;

      HallOfFame *m_hall_of_fame;

      int m_generation;

      // Keep statistics.
      Statistics m_stats_avg_fitness;
      Statistics m_stats_max_fitness;
      Statistics m_stats_max_components_used;
      Statistics m_stats_avg_components_used;
      Statistics m_stats_population_size;
      Statistics m_stats_total_components_used;
   };
}


#endif
