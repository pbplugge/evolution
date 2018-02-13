#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H


#include "evolutionary_program.h"
#include "fitness.h"


namespace evolution {
   class ComponentManager;

   /**
    * One individual in evolution.
    */
   class Individual {
   public:
      Individual(ComponentManager *t_component_manager,ComponentLibrary *t_component_library);
      ~Individual();

      double GetAverageFitness(void);
      void SetObjectiveFitness(int t_objective,double t_fitness);

      EvolutionaryProgram *GetEvolutionaryProgram(void);

      bool MutateParameters(double t_mutation_chance);
      bool MutateStructure(double t_mutation_chance);
      void Crossover(Individual *t_parent1, Individual *t_parent2);
      void Randomize(void);

      void Execute(void);
      void CopyFrom(Individual *t_individual);

      bool Dirty(void);
      void ClearDirty(void);
      void Die(void);

      double GetAge(void);
      void SetAge(double);

   private:
      EvolutionaryProgram m_evolutionary_program;

      Fitness m_fitness;

      ComponentManager *m_component_manager;
      ComponentLibrary *m_component_library;

      double m_age;

      // Dirty flag if modified but fitness not calculated.
      bool m_dirty;

      // TODO: Besides evolutionary programs perhaps also give it a genome to evolve.
      // TODO: Perhaps more programs possiible per individual.
   };
}

#endif
