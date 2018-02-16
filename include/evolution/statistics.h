/** @file statistics.h
 *  @brief Keeps track of valuable information during evolution.
 *
 *  It is used in the Population class.
 *  If you use more then 10000 generations, increase MAX_SIZE_STATISTICS.
 */
#ifndef STATISTICS_H
#define STATISTICS_H

// 10k generations to keep track of.
#define MAX_SIZE_STATISTICS 10000


namespace evolution {

   class Statistics {
   public:
      void Set(int t_generation,double t_value);
      int GetLength(void);
      void Clear(void);
      double *Get(void);
      double GetValue(int t_generation);

   private:
      double m_statistic[MAX_SIZE_STATISTICS];
      int m_length;
   };
}

#endif
