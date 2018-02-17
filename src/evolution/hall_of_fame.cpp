#include "../../include/evolution.h"

using namespace evolution;


HallOfFame::HallOfFame(ComponentManager *t_component_manager,ComponentLibrary *t_component_library) {
   int t;
   for (t=0; t<HALL_OF_FAME_INDIVIDUALS ; t++) {
      m_individual[t] = new Individual(t_component_manager,t_component_library);
   }
}

HallOfFame::~HallOfFame() {
   int t;
   for (t=0; t<HALL_OF_FAME_INDIVIDUALS ; t++) {
      delete m_individual[t];
   }
}

void HallOfFame::AddIndividual(Individual *t_individual) {
   //std::cout << "HallOfFame::AddIndividual(): " << t_individual->GetAverageFitness() << "\n";

   // Check its place on the list.
   int t, i = -1;
   for (t=0; t<HALL_OF_FAME_INDIVIDUALS ; t++) {
      if (m_individual[t]->GetAverageFitness() < t_individual->GetAverageFitness()) {
         i = t; // insert at this position.
         t = HALL_OF_FAME_INDIVIDUALS;
      }
   }

   if (i > -1) {
      // Move all individuals below down.
      Individual *n = m_individual[HALL_OF_FAME_INDIVIDUALS-1];
      for (t=HALL_OF_FAME_INDIVIDUALS-1; t>i; t--) {
         m_individual[t] = m_individual[t-1];
      }
      m_individual[i] = n;
      n->CopyFrom(t_individual);
   }

   //Debug();
}

/**
 * Show the individuals in the hall of fame.
 */
void HallOfFame::Debug(void) {
   std::cout << "HallOfFame::Debug():\n";
   for (int t=0; t<HALL_OF_FAME_INDIVIDUALS ; t++) {
      std::cout << (t+1) << ") " << m_individual[t]->GetAverageFitness() << "\n";
   }
}
