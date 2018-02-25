/** @file sequential_data.cpp
 *  @brief How to learn to do actions based on changes.
 *
 *
 *  output 1: when the input changes value i want the output to be increased.
 *  output 2: of an input sine, when the value gets above 0.9 or below 0.1 the output toggles.
 */

#include "../../include/evolution.h"
#include <cmath>

using namespace evolution;

extern ThreadManager *thread_manager;
#define PI 3.14159265


class SequentialData: public evolution::Thread {
public:

   void Init(void) {
      GetConfig()->SetMinimumPopulationSize(40);
      GetConfig()->SetMaximumPopulationSize(100);

      GetConfig()->SetStructureMutationChance(0.5f);
      GetConfig()->SetParameterMutationChance(0.5f);

      input_type = new ComponentTypeInput;
      output_type = new ComponentTypeOutput;
      AddComponentType(input_type);
      AddComponentType(output_type);
      AddComponentType(new ComponentTypeThreshold);
      AddComponentType(new ComponentTypeChangeDetector);
      AddComponentType(new ComponentTypeCounter);

      // The input of our system has 2 outputs and the output of our system has 2 inputs.
      input_type->SetNumberOfOutputs(2);
      input_type->SetOutputType(0,component_node_type_int);    // number.
      input_type->SetOutputType(1,component_node_type_double); // (sine)

      output_type->SetNumberOfInputs(2);
      input_type->SetInputType(0,component_node_type_int);  // output number.
      input_type->SetInputType(0,component_node_type_bool);  // threshold.

      GetConfig()->SetRandomizeAfterGenerationsWithoutImprovement(10);
   }


   void CalculateFitness(evolution::Individual *t_individual) {
      int t;
      double i1,o1;
      double i2,o2;
      double e1 = 0;
      double e2 = 0;

      Component *input = t_individual->GetEvolutionaryProgram()->GetComponentOfType(input_type);
      Component *output = t_individual->GetEvolutionaryProgram()->GetComponentOfType(output_type);

      if (!input || !output)
         return;

      t_individual->GetEvolutionaryProgram()->ResetComponentsForNextSimulation();

      for (t=0; t<100; t++) {
         // 1 period sine on input 1 between 0 and 1.
         i1 = 0.5 + sin ((double)t*PI/50)/2;
         input->SetOutputValue(0,i1);

         //std::cout << "sin("<< t << ") = " << i1 << "\n";

         // change value on input 2.
         i2 = (double)(20 - int(t/5));
         input->SetOutputValue(1,i2);

         // simulate.
         t_individual->Execute();

         // compare to expected value and add to error.
         o1 = output->GetInputValue(0);
         o2 = output->GetInputValue(1);

         // Error of output 1.
         if (int(o1) != int(t/5)+1) {
            e1 = e1 + 1;
         }

         // Error of output 2.
         if (t <= 15) {
            if (o2 != 0.0f) e2 = e2 + 1;
         } else if (t <= 65) {
            if (o2 != 1.0f) e2 = e2 + 1;
         } else {
            if (o2 != 0.0f) e2 = e2 + 1;
         }
      }

      // Average error.
      e1 /= 100.0f;
      e2 /= 100.0f;

      //std::cout << "errors: " << e1 << ", " << e2 << "\n";

      // Calculate fitness from error.
      // fitness = 1 - error
      t_individual->SetObjectiveFitness(0,1-e1);
      t_individual->SetObjectiveFitness(1,1-e2);
   }

   /**
    * Quit either after 1000 generations or a perfect candidate was found.
    */
   bool ContinueEvolution(void) {
      int g = m_population.GetGeneration();
      std::cout << "generation: " << g << " ";
      std::cout << "fittest individual: " << m_population.GetHallOfFame()->GetIndividual(0)->GetAverageFitness() << "\n";

      if (g == 1000 || m_population.GetIndividual(0)->GetAverageFitness() == 1)
         return false;

      return true;
   }

private:
   ComponentTypeInput *input_type;
   ComponentTypeOutput *output_type;
};


extern "C" void experiment_sequential_data(void) {
   init();

   SequentialData *domain = new SequentialData();

   thread_manager->StartThread(domain);

   thread_manager->Wait();
}
