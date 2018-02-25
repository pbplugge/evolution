/** @file adding_two_numbers.cpp
 *  @brief Evolution that generates a formula using addition to get the number 1.5.
 */
#include <cmath>
#include "../../include/evolution.h"

using namespace evolution;

extern ThreadManager *thread_manager;


// Experiment to aproach a mathematical formula x + y = 1.5.
class MathematicalFormulaApproacher: public evolution::Thread {
public:
   ~MathematicalFormulaApproacher(){
      std::cout << "MathematicalFormulaApproacher::~MathematicalFormulaApproacher()\n";
   }

   // Add components we want to use to the library.
   void Init(void) {
      std::cout << "MathematicalFormulaApproacher::Init()\n";
      GetConfig()->SetMinimumPopulationSize(5);
      GetConfig()->SetMaximumPopulationSize(6);

      component_add = new ComponentTypeAdd();
      component_add->SetMaximumComponents(1);
      component_add->SetRequiredComponents(1);
      AddComponentType(component_add);

      component_input = new ComponentTypeParameterAsOutput();
      component_input->SetMaximumComponents(2);
      component_input->SetRequiredComponents(2);
      AddComponentType(component_input);
   }

   // Required fitness function.
   void CalculateFitness(evolution::Individual *t_individual) {
      // Execute here because for some problems you need more cycles.
      t_individual->Execute();

      // Get the Add component.
      Component *c = t_individual->GetEvolutionaryProgram()->GetComponentOfType(component_add);

      //
      double v = 0;
      if (c) {
         //std::cout << "MathematicalFormulaApproacher::CalculateFitness() -> no error.\n";
         // Objective 1: the system has a non zero output.
         if (c->GetOutputNode(0)->GetValue() != 0.0f) {
            t_individual->SetObjectiveFitness(0,1.0f);
         } else {
            t_individual->SetObjectiveFitness(0,0.0f);
         }

         // Objective 2: the output must be equal to 4.
         v = c->GetOutputNode(0)->GetValue();
         double fitness = 1 - (fabs(v-1));
         t_individual->SetObjectiveFitness(1,fitness);

         // Objective 3: both inputs must be connected to different components.
         if (c->GetInputNode(0)->IsConnected() && c->GetInputNode(1)->IsConnected()) {
            if (c->GetInputNode(0)->GetConnectedTo()->GetComponent() != c->GetInputNode(1)->GetConnectedTo()->GetComponent()){
               t_individual->SetObjectiveFitness(2,1);
            } else {
               t_individual->SetObjectiveFitness(2,0);
            }
         } else {
            t_individual->SetObjectiveFitness(2,0);
         }
      } else {
         std::cout << "MathematicalFormulaApproacher::CalculateFitness() -> ERROR: There is no add component in the individual 1 is required." << t_individual->GetEvolutionaryProgram()->GetComponentCount() << "\n";
         t_individual->SetObjectiveFitness(0,0.0f);
         t_individual->SetObjectiveFitness(1,0.0f);
      }
   }

   // Whatever condition you may have to stop evolution.
   bool ContinueEvolution(void){
      //m_population.SortOnFitness();
      double fitness = m_population.GetIndividual(0)->GetAverageFitness();
      std::cout << "Fitness: " << fitness << "\n";
      if (fitness > 0.99 || m_population.GetGeneration() == 1000) {
         return false;
      }
      return true;
   }
private:
   ComponentType *component_add;
   ComponentType *component_input;
};



extern "C" void experiment_adding_two_numbers(void) {
   init();

   MathematicalFormulaApproacher *domain = new MathematicalFormulaApproacher();

   thread_manager->StartThread(domain);

   thread_manager->Wait();

   // Since we want to use this data from python notebook we can't delete the thread here.
}


