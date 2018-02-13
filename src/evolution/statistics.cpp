#include "../../include/evolution.h"


using namespace evolution;


void Statistics::Set(int t_generation,double t_value) {
   if (t_generation >= MAX_SIZE_STATISTICS) {
      std::cout << "Statistics::Set() -> Maximum statistics size met.\n";
      return;
   }
   m_statistic[t_generation] = t_value;
   if (t_generation > m_length)
      m_length = t_generation + 1;
}

int Statistics::GetLength(void) {
   return m_length;
}

void Statistics::Clear(void) {
   m_length = 0;
}

double *Statistics::Get(void) {
   return &m_statistic[0];
}

double Statistics::GetValue(int t_generation) {
   return m_statistic[t_generation];
}
