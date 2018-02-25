#include "../../../include/evolution.h"


using namespace evolution;


ComponentTypeCounter::ComponentTypeCounter() {
   m_number_of_inputs = 1;
   m_number_of_outputs = 1;
   m_number_of_parameters = 1;
   m_name = "ComponentTypeCounter";
   m_input_node_type[0] = component_node_type_bool;
   m_output_node_type[0] = component_node_type_int;

   m_max_number_of_components = 3;
   m_req_number_of_components = 0;
}

void ComponentTypeCounter::Execute(Component *t_component) {
   double v = t_component->GetInputNode(0)->GetValue();

   if (int(v) == 1) {
      v = t_component->GetOutputValue(0);
      t_component->SetOutputValue(0,v+1);
   }
}

void ComponentTypeCounter::ResetForNextSimulation(Component *t_component) {
   t_component->SetOutputValue(0,0.0f);
}
