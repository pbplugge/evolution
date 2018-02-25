#include "../../include/evolution.h"


using namespace evolution;


Population::Population() {
   m_minimum_number_of_active_members = 0;
   m_individual = 0;
   m_generation = 0;
   m_maximum_number_of_numbers = 0;
   m_number_of_active_members = 0;
   m_hall_of_fame = 0;
}


Population::~Population() {
   if (m_individual) {
      for (int t=0; t<m_maximum_number_of_numbers; t++) {
         delete m_individual[t];
      }

      delete[] m_individual;
   }
   if (m_hall_of_fame)
      delete m_hall_of_fame;

   //std::cout << "Population::~Population() done\n";
}

/**
 * Creates 't_minimum_number_of_active_members' random individuals.
 */
void Population::CreatePopulation(int t_minimum_number_of_active_members,int t_maximum_number_of_numbers, ComponentLibrary *t_component_library){
   int t;

   m_individual = new Individual*[t_maximum_number_of_numbers];

   m_maximum_number_of_numbers = t_maximum_number_of_numbers;
   m_minimum_number_of_active_members = t_minimum_number_of_active_members;

   m_hall_of_fame = new HallOfFame(&m_component_manager,t_component_library);

   for (t=0; t<t_maximum_number_of_numbers; t++) {
      m_individual[t] = new Individual(&m_component_manager,t_component_library);
   }

   for (t=0; t<m_minimum_number_of_active_members; t++) {
      CreateRandomIndividual();
   }
}

int Population::GetGeneration(void) {
   return m_generation;
}

void Population::IncreaseGeneration(void) {
   m_generation ++;
}

/**
 * Sorts population by fitness descending.
 */
void Population::SortOnFitness(void) {
   int t;
   bool sort_done = false;

   while (!sort_done) {
      sort_done = true;

      // From 1-100 to 0-98 (t+1 must be an individual).
      for (t = 0; t < m_number_of_active_members - 2; t++) {
         if (m_individual[t]->GetAverageFitness() < m_individual[t + 1]->GetAverageFitness()) {
            // Sorting not done.
            sort_done = false;

            // Flip the systems.
            Individual *b = m_individual[t];
            m_individual[t] = m_individual[t + 1];
            m_individual[t + 1] = b;
         }
      }
   }
}

/**
 * TODO: Want ro depricate this and always use the sortonfitness function.
 */
void Population::RepositionIndividualOnFitness(int t_index) {
   int t;
   Individual *i = m_individual[t_index];
   double fitness = i->GetAverageFitness();

   if (t_index > 0) {
      // Fitness if greater, move other individuals.
      for (t=t_index-1; fitness > m_individual[t]->GetAverageFitness() && t>0; t--) {
         m_individual[t+1] = m_individual[t];
         m_individual[t] = i;
      }
   }

   if (t_index < m_number_of_active_members-2) {
      for (t=t_index+1; m_individual[t]->GetAverageFitness() < fitness && t<m_number_of_active_members-2; t++) {
         m_individual[t-1] = m_individual[t];
         m_individual[t] = i;
      }
   }
}

int Population::GetNumberOfActiveMembers(void) {
   return m_number_of_active_members;
}


void Population::MutateStructures(double t_mutation_chance) {
   if (t_mutation_chance == 0.0f)
      return;

   for (int t = 0; t < m_number_of_active_members; t++) {
      if (m_individual[t]->MutateStructure(t_mutation_chance)){
         RepositionIndividualOnFitness(t);
      }
   }
}

void Population::MutateParameters(double t_mutation_chance) {
   if (t_mutation_chance == 0.0f)
      return;

   for (int t = 0; t < m_number_of_active_members; t++) {
      if (m_individual[t]->MutateParameters(t_mutation_chance)){
         RepositionIndividualOnFitness(t);
      }
   }
}

/**
 * The best individual has a % chance of being selected, the percentage gets reduced at each member.
 */
Individual *Population::GetRandomParent(void) {
   int t;
   double r = ((double) rand() / (RAND_MAX));
   int p = -1;

   for (t=0; t<m_number_of_active_members; t++) {
      if (p == -1) {
         if (r < 0.03) {
            return m_individual[t];
         } else {
            r *= 0.97;
         }
      }
   }

   return 0;
}

void Population::DoCrossOver(double t_crossover_chance) {
   if (t_crossover_chance == 0.0f)
      return;

   if (m_number_of_active_members >= m_maximum_number_of_numbers)
      return;

   Individual *p1 = GetRandomParent();
   Individual *p2 = GetRandomParent();
   Individual *child = m_individual[m_number_of_active_members];
   m_number_of_active_members ++;

   child->Crossover(p1,p2);
}

void Population::RemoveWeakestFromPopulation(void) {

}

Individual *Population::GetIndividual(int t_index) {
   return m_individual[t_index];
}

void Population::CreateRandomIndividual(void) {
   if (m_number_of_active_members >= m_maximum_number_of_numbers)
      return;

   //std::cout << "Population::CreateRandomIndividual() -> id=" << m_number_of_active_members << "\n";
   m_individual[m_number_of_active_members]->Randomize();
   m_number_of_active_members ++;
   RepositionIndividualOnFitness(m_number_of_active_members-1);
}

/**
 * Update hall of fame with best individual which should be sorted at the top.
 */
void Population::UpdateHallOfFame(void) {
   m_hall_of_fame->AddIndividual(m_individual[0]);
}

/**
 * Calculate statistics.
 */
void Population::UpdateStatistics(void) {
   int t;
   double f, avgf = 0,maxf = 0,avgc;
   int c, maxc = 0;

   // Calc it.
   for (t=0; t<m_number_of_active_members; t++) {
      f = m_individual[t]->GetAverageFitness();
      avgf += f;
      if (f > maxf) maxf = f;

      c = m_individual[t]->GetEvolutionaryProgram()->GetComponentCount();
      if (c > maxc) maxc = c;
      avgc += (double)c;
   }

   avgf /= (double)m_number_of_active_members;
   avgc /= (double)m_number_of_active_members;

   m_stats_avg_fitness.Set(m_generation,avgf);
   m_stats_max_fitness.Set(m_generation,maxf);
   m_stats_avg_components_used.Set(m_generation,avgc);;
   m_stats_max_components_used.Set(m_generation,(double)maxc);
   m_stats_population_size.Set(m_generation,(double)m_number_of_active_members);
   m_stats_total_components_used.Set(m_generation,(double)m_component_manager.GetComponentCount());
}

Statistics *Population::GetStatsAvgFitness(void) {
   return &m_stats_avg_fitness;
}

Statistics *Population::GetStatsMaxFitness(void) {
   return &m_stats_max_fitness;
}

Statistics *Population::GetStatsAvgComponentsUsed(void) {
   return &m_stats_avg_components_used;
}

Statistics *Population::GetStatsMaxComponentsUsed(void) {
   return &m_stats_max_components_used;
}

Statistics *Population::GetStatsPopulationSize(void) {
   return &m_stats_population_size;
}

Statistics *Population::GetStatsTotalComponentsUsed(void){
   return &m_stats_total_components_used;
}

/**
 * Clean up existing individuals if size decreased.
 * Create new random individuals if size increased.
 */
void Population::SetNumberOfActiveMembers(int t_number_of_active_members) {
   int t;

   // Clean up existing individuals if size decreased.
   if (t_number_of_active_members < m_number_of_active_members) {
      for (t=m_number_of_active_members-1; t>=t_number_of_active_members; t--) {
         std::cout << "Population::SetNumberOfActiveMembers() -> individual[" << t << "] dies\n";
         m_individual[t]->Die();
      }
      m_number_of_active_members = t_number_of_active_members;
   }

   // Create new random individuals if size increased.
   else if (t_number_of_active_members > m_number_of_active_members) {
      for (t=m_number_of_active_members; t<t_number_of_active_members; t++) {
         CreateRandomIndividual();
      }
   }
}

/**
 * Every individual has a chance to be a parent equal to its fitness.
 * https://en.wikipedia.org/wiki/Fitness_proportionate_selection
 *
 * TODO: select on niches. i.e. individual is good in one particular objective.
 */
void Population::CreateIndividualFromCrossOver(int t_index) {
   double total_fitness = 0.0f,f;
   int t,p1 = -1,p2 = -1;

   std::cout << "Population::CreateIndividualFromCrossOver() -> id=" << t_index << "\n";

   // Calculate total fitness.
   for (t=0; t<m_number_of_active_members; t++) {
      if (t != t_index)
         total_fitness += m_individual[t]->GetAverageFitness();
   }

   // If population has no fitness randomize the individual.
   if (total_fitness == 0.0f) {
      m_individual[t_index]->Randomize();
      return;
   }

   // Random number between 0 and total_fitness.
   double random_1 = ((double) rand() / (RAND_MAX)) * total_fitness;
   double random_2 = ((double) rand() / (RAND_MAX)) * total_fitness;

   // Now look what parents the numbers belong to the first member has a % chance of being a parent. the chance is reduced by % with each member.
   for (t=0; t<m_number_of_active_members; t++) {
      if (t != t_index) {
         f = m_individual[t]->GetAverageFitness();

         if (p1 == -1) {
            if (random_1 < f)            p1 = t;
            random_1 -= f;
         }
         if (p2 == -1) {
            if (random_2 < f)            p2 = t;
            random_2 -= f;
         }

         // break loop if both parents found.
         if (p1 >=0 && p2 >= 0)
            t = m_number_of_active_members;
      }
   }

   if (p1 >= 0 && p2 >= 0) {
      std::cout << "Population::CreateIndividualFromCrossOver() -> parents found: " << p1 << " and " << p2 << " for individual " << t_index << "\n";
      m_individual[t_index]->Crossover(m_individual[p1],m_individual[p2]);

      std::cout << "Population::DoCrossOver() -> child " << t_index  << " has " << m_individual[t_index]->GetEvolutionaryProgram()->GetComponentCount() << " components\n";

      if (!m_individual[t_index]->GetEvolutionaryProgram()->GetComponentCount()) {
         std::cout << "Population::CreateIndividualFromCrossOver() -> Error crossing over 2 individuals with " << m_individual[p1]->GetEvolutionaryProgram()->GetComponentCount() << " and " << m_individual[p2]->GetEvolutionaryProgram()->GetComponentCount() << " components\n";
         exit(0);
      }

   } else {
      std::cout << "Population::CreateIndividualFromCrossOver() -> Error while looking for parents: " << p1 << ", " << p2 << "\n";
      exit(0);
   }
}

/**
 * Check for things that may not occur.
 * Its for testing purposes only.
 * It exits when an error is found.
 */
void Population::CheckForErrors(void) {
   int t;

   for (t=0; t<m_number_of_active_members; t++) {
      if (m_individual[t]->GetEvolutionaryProgram()->GetComponentCount() == 0) {
         std::cout << "Population::CheckForErrors() -> Individual[" << t << "] has no components.\n";
         exit(0);
      }
   }
}

HallOfFame *Population::GetHallOfFame(void) {
   return m_hall_of_fame;
}


