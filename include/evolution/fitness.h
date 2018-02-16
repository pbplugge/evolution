/** @file fitness.h
 *  @brief Implementation of multi-objective fitness.
 *
 *  TODO: There are more ways of determining fitness.
 *        Some objectives may be requirements and others nice to haves.
 */
#ifndef FITNESS_H
#define FITNESS_H


#define MAX_NUMBER_OF_FITNESS_OBJECTIVES 20

namespace evolution {

   class Fitness {
   public:
      Fitness();
      void SetObjectiveFitness(int t_objective,double t_fitness);
      double GetObjectiveFitness(int t_objective);

      double GetAverageFitness(void);
      void CopyFrom(Fitness *t_fitness);

   private:
      double m_fitness[MAX_NUMBER_OF_FITNESS_OBJECTIVES];
      int m_number_of_objectives;

      double m_average_fitness;

      void CalculateAverageFitness(void);
   };

}


#endif
