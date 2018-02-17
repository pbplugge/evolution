/** @file traveling_salesman.cpp
 *  @brief Will solve the traveling salesman problem.
 *
 *  The order of the components is all that matters.
 *  So we want o only do ordering mutations.
 */
#include <iostream>
#include <cmath>
#include "../../include/evolution.h"

#define TSP_NUMBER_OF_POINTS 10

using namespace evolution;

extern ThreadManager *thread_manager;


// Create component type for adding.
class TSPCoordinate:public ComponentType {
public:
   TSPCoordinate() {
      m_number_of_inputs = 0;
      m_number_of_outputs = 0;
      m_number_of_parameters = 2;
      m_name = "coordinate";
      m_max_number_of_components = TSP_NUMBER_OF_POINTS;
      m_req_number_of_components = TSP_NUMBER_OF_POINTS;
   }

   // Execute is required but in this case does not do anything.
   void Execute(Component *t_component) {}
};


// Experiment to aproach a mathematical formula 1+3 = 4.
class TSP: public evolution::Thread {
public:
   ~TSP(){
      std::cout << "TSP::~TSP()\n";
   }

   double CalculateDistance(double x1,double y1,double x2,double y2) {
      double a = (x2 - x1) * (x2 - x1);
      double b = (y2 - y1) * (y2 - y1);

      return sqrt(a + b);
   }

   // Add components we want to use to the library.
   void Init(void) {
      GetConfig()->SetMinimumPopulationSize(40);
      GetConfig()->SetMaximumPopulationSize(100);
      AddComponentType(new TSPCoordinate());

      // Generate random coordinates.
      for (int t=0; t<TSP_NUMBER_OF_POINTS; t++) {
         m_coordinate_x[t] = (double)rand() * 100 / RAND_MAX;
         m_coordinate_y[t] = (double)rand() * 100 / RAND_MAX;
         std::cout << "TSP::Init() -> coordinate[" << t << "] = (" << m_coordinate_x[t] << "," << m_coordinate_y[t] << ")\n";
      }

      // Are the coordinates set inside the individual.
      m_coordinates_set = false;
   }

   // Required fitness function.
   void CalculateFitness(evolution::Individual *t_individual) {
      int t;
      EvolutionaryProgram *p = t_individual->GetEvolutionaryProgram();
      Component *c1,*c2;
      double distance = 0;

      if (p->GetComponentCount() < TSP_NUMBER_OF_POINTS) {
         std::cout << "TSP::CalculateFitness() -> individual has " << p->GetComponentCount() << " components\n";
         exit(1);
      }

      // Now calculate all distances between the points.
      for (t=0; t<TSP_NUMBER_OF_POINTS-1; t++) {
         c1 = p->GetComponentAt(t);
         c2 = p->GetComponentAt(t+1);
         distance += CalculateDistance(c1->GetParameterValue(0),c1->GetParameterValue(1),c2->GetParameterValue(0),c2->GetParameterValue(1));
      }

      if (distance == 0) {
         std::cout << "TSP::CalculateFitness() -> individual has no distance\n";
         exit(1);
      }

      // Set fitness equal to 1000-distance because we want the minimum distance.
      t_individual->SetObjectiveFitness(0,10000 - distance);

      // If you would want the longest distance between the points just do this instead.
      //t_individual->SetObjectiveFitness(0,distance);
   }

   // Implement own algorithm since we are only interested in the order of the components.
   // We use the best individual and copy/mutate it for the rest of the population.
   void DoAlgorithm(void) {
      int t,t2;
      Individual *i,*best;
      Component *c;
      EvolutionaryProgram *p;

      // Check if all components have a coordinate,
      // parameter 0  and parameter 1  are used for the coordinate.
      if (!m_coordinates_set) {
         m_coordinates_set = true;
         for (t=0; t<m_population.GetNumberOfActiveMembers(); t++) {
            i = m_population.GetIndividual(t);
            p = i->GetEvolutionaryProgram();
            for (t2=0; t2<TSP_NUMBER_OF_POINTS; t2++) {
               c = p->GetComponentAt(t2);
               c->SetParameterValue(0,m_coordinate_x[t2]);
               c->SetParameterValue(1,m_coordinate_y[t2]);
            }
         }
      }

      // Copy to all others with one component flip.
      best = m_population.GetIndividual(0);
      for (t=1; t<m_population.GetNumberOfActiveMembers(); t++) {
         i = m_population.GetIndividual(t);
         i->CopyFrom(best);
         i->GetEvolutionaryProgram()->FlipTwoRandomComponents();
         CalculateFitness(i);
      }

      // Resort the population on fitness.
      m_population.SortOnFitness();

      best = m_population.GetIndividual(0);
      std::cout << "TSP::DoAlgorithm() -> Best fitness: " << best->GetAverageFitness() << "\n";
   }

   // I want to stop after 100 generations..
   bool ContinueEvolution(void) {
      if (m_population.GetGeneration() == 10)
         return false;
      return true;
   }

private:
   ComponentType *m_component_coordinate;
   bool m_coordinates_set;
   double m_coordinate_x[TSP_NUMBER_OF_POINTS];
   double m_coordinate_y[TSP_NUMBER_OF_POINTS];
};


// Experiment traveling salesman problem.
extern "C" void experiment_traveling_salesman_problem(void) {
   init();

   TSP *traveling_salesman_problem = new TSP();

   thread_manager->StartThread(traveling_salesman_problem);

   thread_manager->Wait();
}


// Function to get the traveling salesman coordinates.
extern "C" double *get_tsp_coordinates(void) {
   double *f = (double*) malloc ( sizeof(double) * TSP_NUMBER_OF_POINTS * 2);

   for (int t=0; t<TSP_NUMBER_OF_POINTS; t++) {
      f[t*2] = thread_manager->GetThread(0)->GetPopulation()->GetIndividual(0)->GetEvolutionaryProgram()->GetComponentAt(t)->GetParameterValue(0);
      f[t*2 + 1] = thread_manager->GetThread(0)->GetPopulation()->GetIndividual(0)->GetEvolutionaryProgram()->GetComponentAt(t)->GetParameterValue(1);
   }

   return f;
}

