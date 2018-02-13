#ifndef HALL_OF_FAME_H
#define HALL_OF_FAME_H


namespace evolution {
   class Individual;

   #define HALL_OF_FAME_INDIVIDUALS 10

   /**
    * To keep track of the best individuals during evolution.
    */
   class HallOfFame {
   public:
      HallOfFame(ComponentManager *t_component_manager,ComponentLibrary *t_component_library);
      ~HallOfFame();

      void AddIndividual(Individual *t_individual);
   private:
      Individual *m_individual[HALL_OF_FAME_INDIVIDUALS];

      void Debug(void);
   };
}

#endif
