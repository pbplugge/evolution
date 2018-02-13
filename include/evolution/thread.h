#ifndef EVOLUTION_MAIN_H
#define EVOLUTION_MAIN_H


#include "component_manager.h"
#include "config.h"
#include "population.h"
#include "component_library.h"


/**
 * Parent class for your evoluton implementation.
 * It controlls the evolution.
 * It contains the configuration and population.
 */
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

      void AddComponentType(ComponentType *t_component_type);

   private:
      bool m_stop;

      // The configuration.
      Config m_config;

      // Population.
      Population m_population;

      // Components allowed in the evolution.
      ComponentLibrary m_component_library;

      //void Debug(std::string fn, std::string msg, bool error = false);

      // TODO: keep track of simulation time per cycle.

   };
}

#endif

