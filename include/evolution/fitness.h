#ifndef FITNESS_H
#define FITNESS_H


namespace evolution {

   /**
    * Implementation of multi objective fitness.
    */
   class Fitness {
   public:
      Fitness();
      void SetObjectiveFitness(int t_objective,double t_fitness);
      double GetObjectiveFitness(int t_objective);

      double GetAverageFitness(void);
      void CopyFrom(Fitness *t_fitness);

      // TODO: There are more ways of determining fitness. First objectives may be requirements so average fitness won't work well.
   private:
      double m_fitness[20];
      int m_number_of_objectives;

      double m_average_fitness;

      void CalculateAverageFitness(void);
   };

}


#endif
