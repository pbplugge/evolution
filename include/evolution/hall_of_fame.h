/** @file hall_of_fame.h
 *  @brief Keeps track of the best individuals that ever existed during simulation.
 *
 *  TODO: Does not yet check on doubles.
 */
#ifndef HALL_OF_FAME_H
#define HALL_OF_FAME_H


namespace evolution {
   class Individual;

   #define HALL_OF_FAME_INDIVIDUALS 10

   class HallOfFame {
   public:
      HallOfFame(ComponentManager *t_component_manager,ComponentLibrary *t_component_library);
      ~HallOfFame();

      void AddIndividual(Individual *t_individual);
      Individual *GetIndividual(int t);
   private:
      Individual *m_individual[HALL_OF_FAME_INDIVIDUALS];

      void Debug(void);
   };
}

#endif
