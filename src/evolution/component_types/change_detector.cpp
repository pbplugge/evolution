#include "../../../include/evolution.h"


using namespace evolution;




ComponentTypeChangeDetector::ComponentTypeChangeDetector() {
   m_number_of_inputs = 1;
   m_number_of_outputs = 1;
   m_number_of_parameters = 1;
   m_name = "ComponentTypeChangeDetector";
   m_input_node_type[0] = component_node_type_int;
   m_output_node_type[0] = component_node_type_bool;

   m_max_number_of_components = 3;
   m_req_number_of_components = 0;
}


void ComponentTypeChangeDetector::Execute(Component *t_component) {
   double v = t_component->GetParameterValue(10);
   double newv = t_component->GetInputNode(0)->GetValue();

   if (int(v) != int(newv)) {
      t_component->SetOutputValue(0,1.0f);
   } else {
      t_component->SetOutputValue(0,0.0f);
   }

   t_component->SetParameterValue(10,newv);
}

void ComponentTypeChangeDetector::ResetForNextSimulation(Component *t_component) {
   t_component->SetParameterValue(10,0.0f);
}
