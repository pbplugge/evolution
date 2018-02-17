/** @file config.h
 *  @brief Configuration of the evolution.
 *
 *  Basically getters and setters of hyper parameters.
 *  Its an abstraction so we don't have all this stuff in the Thread class.
 *
 *  TODO: make speed of aging & target age configurable.
 */
#ifndef EVOLUTION_CONFIG_H
#define EVOLUTION_CONFIG_H


namespace evolution {
   class Individual;

   class Config {
   public:
      Config();

      void SetPopulationSize(int);
      int GetPopulationSize(void);

      void SetMinimumPopulationSize(int p);
      int GetMinimumPopulationSize(void);

      void SetMaximumPopulationSize(int);
      int GetMaximumPopulationSize(void);

      int GetMaximumGenerations(void);
      void SetMaximumGenerations(int);

      double GetStructureMutationChance(void);
      void SetStructureMutationChance(double);

      double GetParameterMutationChance(void);
      void SetParameterMutationChance(double);

      void SetCrossoverChance(double t_crossover_chance);
      double GetCrossoverChance(void);

      void SetRandomIndividualChance(double t_random_individual_chance);
      double GetRandomIndividualChance(void);

   private:
      int m_maximum_number_of_generations;
      int m_minimum_population_size;
      int m_maximum_population_size;

      double m_structure_mutation_chance;
      double m_parameter_mutation_chance;
      double m_crossover_chance;
      double m_random_individual_chance;
   };
}

#endif
