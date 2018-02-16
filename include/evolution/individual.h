/** @file individual.h
 *  @brief A single individual.
 *
 *  The individual contains the evolutionary program.
 *  Its fitness should only be re-calculated when marked dirty to safe processor time.
 *  The age is calculated depending on the evolutionary algorithm used.
 *  Its implemented in the Thread class.
 *
 *  TODO: Perhaps more separate evolvable programs possible per individual.
 */
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
      // The definition of the individual.
      EvolutionaryProgram m_evolutionary_program;

      Fitness m_fitness;

      // Just references to the originals.
      ComponentManager *m_component_manager;
      ComponentLibrary *m_component_library;

      // Individuals can die from old age.
      double m_age;

      // Dirty flag if changed but fitness not calculated.
      bool m_dirty;
   };
}

#endif
