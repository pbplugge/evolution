/** @file thread.h
 *  @brief Parent class for evolution implementations.
 *
 *  It controls the evolution.
 *  The method of evolution is implemented here.
 *  It contains the configuration and population.
 */
#ifndef EVOLUTION_MAIN_H
#define EVOLUTION_MAIN_H


#include "component_manager.h"
#include "config.h"
#include "population.h"
#include "component_library.h"


namespace evolution {
   class Thread {
   public:
      Thread();
      virtual ~Thread();


      Config *GetConfig(void) { return &m_config; }
      Population *GetPopulation(void) { return &m_population; }
      ComponentLibrary *GetComponentLibrary(void) { return &m_component_library; }

      // The main loop, start after it is configured.
      void Start(void);
      void Stop(void);

      virtual void Init(void){}
      virtual void CalculateFitness(Individual *i){}
      virtual bool ContinueEvolution(void){ return true; }

      void AddComponentType(ComponentType *t_component_type);

   protected:
      // Population.
      Population m_population;

      // The configuration.
      Config m_config;

      // Components allowed in the evolution.
      ComponentLibrary m_component_library;

      // Algorithms.
      virtual void DoAlgorithm(void);

      void APGA(void);
      void MutateExistingPopulation(void);
      void CreatePopulationFromBest(void);

   private:
      bool ResetAfterGenerationsWithoutImprovement(void);

      int m_generations_without_improvement;
      double m_fittest;

      bool m_stop;


      // TODO: keep track of simulation time per generation.
      // Statistics m_time_per_generation.
   };
}

#endif

