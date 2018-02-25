/** @file using_custom_data_in_components.cpp
 *  @brief tests/illustrates usage of data in components.
 *
 *  In this test an array of 10 integers with an average value of 5 is added to a component.
 *  On execution the average value is calculated and could be used as an output of the component.
 */
#include <iostream>
#include "../../include/evolution.h"

using namespace evolution;

extern ThreadManager *thread_manager;



class ComponentTypeWithData:public ComponentType {
public:
   ComponentTypeWithData() {
      m_number_of_inputs = 0;
      m_number_of_outputs = 0;
      m_number_of_parameters = 0;
      m_name = "component with data";
      m_max_number_of_components = 1;
      m_req_number_of_components = 1;
   }

   ~ComponentTypeWithData() {}

   // Here we use the custom data.
   // As an example we calculate the average value which is 5.
   void Execute(Component *t_component) {
      int t,total = 0;
      int *i = (int*)t_component->GetCustomData();

      for (t=0;t<10; t++){
         total += i[t];
      }

      std::cout << "ComponentTypeWithData::Execute() -> Average value = " << (total / 10) << "\n";
   }

   // Create some data.
   void InitComponent(Component *t_component) {
      int *i = new int[10];
      t_component->SetCustomData((void*)&i[0]);

      // just set some test values.
      for (int t=0; t<10; t++) {
         i[t] = t+1;
      }
   }

   // Delete the data.
   void ClearComponent(Component *t_component) {
      int *i = (int*)t_component->GetCustomData();
      if (!i) {
         std::cout << "ComponentTypeWithData::ClearComponent() -> Error: component has no data\n";
         exit(1);
      }
      delete[] i;
   }

};


// Experiment with custom data in components.
class CustomDataInComponents: public evolution::Thread {
public:
   ~CustomDataInComponents() {
      std::cout << "CustomDataInComponents::~CustomDataInComponents()\n";
   }

   // Add components we want to use to the library.
   void Init(void) {
      std::cout << "CustomDataInComponents::Init()\n";
      GetConfig()->SetMinimumPopulationSize(1);
      GetConfig()->SetMaximumPopulationSize(100);

      AddComponentType(new ComponentTypeWithData());
   }

   // Required fitness function.
   void CalculateFitness(evolution::Individual *t_individual) {
      t_individual->Execute();
      t_individual->SetObjectiveFitness(0,0);
   }

   // Whatever condition you may have to stop evolution.
   bool ContinueEvolution(void) {
      if (m_population.GetGeneration() == 2)
         return false;
      return true;
   }
};




// Experiment custom data.
extern "C" void experiment_using_components_with_custom_data(void) {
   init();

   CustomDataInComponents *datatest = new CustomDataInComponents();

   thread_manager->StartThread(datatest);

   thread_manager->Wait();

   delete datatest;
}


