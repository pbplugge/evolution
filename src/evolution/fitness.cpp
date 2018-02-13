#include "../../include/evolution.h"

using namespace evolution;


Fitness::Fitness(){
   m_number_of_objectives = 0;
   m_average_fitness = 0;
}

void Fitness::SetObjectiveFitness(int t_objective,double t_fitness) {
   if (t_objective < 20) {
      m_fitness[t_objective] = t_fitness;
   }
   if (t_objective+1 > m_number_of_objectives)
      m_number_of_objectives = t_objective+1;

   CalculateAverageFitness();
}

double Fitness::GetObjectiveFitness(int t_objective) {
   if (t_objective >=20)
      return 0;
   return m_fitness[t_objective];
}


double Fitness::GetAverageFitness(void) {
   return m_average_fitness;
}

void Fitness::CopyFrom(Fitness *t_fitness) {
   m_number_of_objectives = t_fitness->m_number_of_objectives;
   for (int t=0; t<m_number_of_objectives; t++)
      m_fitness[t] = t_fitness->m_fitness[t];
}

void Fitness::CalculateAverageFitness(void) {
   double f = 0;
   for (int t=0; t<m_number_of_objectives; t++) {
      f += m_fitness[t];
   }
   m_average_fitness = f / (double)m_number_of_objectives;
}
