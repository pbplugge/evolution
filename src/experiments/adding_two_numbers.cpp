/** @file adding_two_numbers.cpp
 *  @brief Evolution that generates a formula to get the number 4.
 */
#include <cmath>
#include "../../include/evolution.h"


using namespace evolution;

extern ThreadManager *thread_manager;

class ComponentTypeAdd;
class ComponentTypeInput;
class MathematicalFormulaApproacher;


// Create component type for adding.
class ComponentTypeAdd:public ComponentType {
public:
   ComponentTypeAdd() {
      m_number_of_inputs = 2;
      m_number_of_outputs = 1;
      m_number_of_parameters = 0;
      m_name = "add";
      m_input_node_type[0] = input_node_type_double;
      m_input_node_type[1] = input_node_type_double;
      m_output_node_type[0] = input_node_type_double;

      m_max_number_of_components = 1;
      m_req_number_of_components = 1;
   }

   void Execute(Component *t_component) {
      double v1 = t_component->GetInputValue(0)*2;
      double v2 = t_component->GetInputValue(1)*6;

      std::cout << "Adding " << v1 << " and " << v2 << ".\n";

      t_component->SetOutputValue(0,v1+v2);
   }
};


// Create component type for input values for the adder.
class ComponentTypeInput:public ComponentType {
public:
   ComponentTypeInput() {
      m_number_of_inputs = 0;
      m_number_of_outputs = 1;
      m_number_of_parameters = 1;
      m_name = "input";
      m_output_node_type[0] = input_node_type_double;

      m_max_number_of_components = 2;
      m_req_number_of_components = 2;
   }

   void Execute(Component *t_component){
      double v = t_component->GetParameterValue(0);

      std::cout << "ComponentTypeInput:Execute() -> " << v << "\n";
      t_component->SetOutputValue(0,v);
   }
};


// Experiment to aproach a mathematical formula 1+3 = 4.
class MathematicalFormulaApproacher: public evolution::Thread {
public:
   ~MathematicalFormulaApproacher(){
      std::cout << "MathematicalFormulaApproacher::~MathematicalFormulaApproacher()\n";
   }

   // Add components we want to use to the library.
   void Init(void) {
      std::cout << "MathematicalFormulaApproacher::Init()\n";
      GetConfig()->SetMinimumPopulationSize(4);
      GetConfig()->SetMaximumPopulationSize(100);

      component_add = new ComponentTypeAdd();
      AddComponentType(component_add);
      AddComponentType(new ComponentTypeInput());
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
         v = c->GetOutputNode(0)->GetValue() / 4;
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
      if (fitness > 0.99) {
         return false;
      }
      return true;
   }
private:
   ComponentType *component_add;
};



extern "C" void experiment_adding_two_numbers(void) {
   init();

   MathematicalFormulaApproacher *domain = new MathematicalFormulaApproacher();

   thread_manager->StartThread(domain);
}


