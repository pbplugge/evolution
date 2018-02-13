#include <iostream>
#include "../../include/evolution.h"


using namespace evolution;
Thread *thread;
extern ThreadManager *thread_manager;


// Create component type for adding.
class ComponentTypeTest:public ComponentType {
public:
   ComponentTypeTest() {
      m_number_of_inputs = 2;
      m_number_of_outputs = 1;
      m_number_of_parameters = 1;
      m_name = "test";
      m_input_node_type[0] = input_node_type_double;
      m_input_node_type[1] = input_node_type_double;
      m_output_node_type[0] = input_node_type_double;

      m_max_number_of_components = 10;
      m_req_number_of_components = 2;
   }

   // Execute doesn't do anything. its just a test.
   void Execute(Component *t_component) {}
};


/**
 * Here i check if all mutation operations work correctly.
 * Use the python notebook example to view the results or use the debug function.
 */
extern "C" void experiment_test_mutations(void) {
   int t;

   init();

   thread = new Thread();

   thread_manager->AddThread(thread);

   thread->AddComponentType(new ComponentTypeTest());
   thread->GetPopulation()->CreatePopulation(4,60,thread->GetComponentLibrary());

   Individual *i[10];
   for (t=0; t<10; t++) {
      i[t] = thread->GetPopulation()->GetIndividual(t);
   }

   // Make 2 random individuals.
   i[0]->Randomize();
   i[1]->Randomize();
   //i[0]->GetEvolutionaryProgram()->Debug();

   // Test crossover.
   i[2]->Crossover(i[0],i[1]);

   // Test copying.
   i[3]->CopyFrom(i[2]);

   // Test add component.
   i[4]->CopyFrom(i[3]);
   i[4]->GetEvolutionaryProgram()->AddRandomComponent();

   // Test remove component.
   i[5]->CopyFrom(i[4]);
   i[5]->GetEvolutionaryProgram()->RemoveRandomComponent();

   // Test remove random nodes.
   i[6]->CopyFrom(i[5]);
   i[6]->GetEvolutionaryProgram()->DisconnectRandomNodes();

   // Test add random nodes.
   i[7]->CopyFrom(i[6]);
   i[7]->GetEvolutionaryProgram()->ConnectRandomNodes();

   // Test flip 2 components.
   i[8]->CopyFrom(i[7]);
   i[8]->GetEvolutionaryProgram()->FlipTwoRandomComponents();

   // Test shuffle.
   i[9]->CopyFrom(i[8]);
   i[9]->GetEvolutionaryProgram()->ShuffleAndReconnect();

   std::cout << "experiment_test_mutations() done\n";
}
