#include "../../../include/evolution.h"


using namespace evolution;



ComponentTypeThreshold::ComponentTypeThreshold(){
   m_number_of_inputs = 1;
   m_number_of_outputs = 1;
   m_number_of_parameters = 1;
   m_name = "ComponentTypeThreshold";
   m_input_node_type[0] = component_node_type_double;
   m_output_node_type[0] = component_node_type_bool;

   m_max_number_of_components = 3;
   m_req_number_of_components = 0;
}


void ComponentTypeThreshold::Execute(Component *t_component) {
   // return if input is not connected.
   if (!t_component->GetInputNode(0)->IsConnected()) {
      return;
   }

   double v = t_component->GetInputNode(0)->GetValue();
   double p1 = t_component->GetParameterValue(0);
   ComponentOutputNode *on = t_component->GetOutputNode(0);

   if (v > 1 - p1) {
      on->SetValue(1.0f);
   } else if (v < p1) {
      on->SetValue(0.0f);
   }
};


void ComponentTypeThreshold::ResetForNextSimulation(Component *t_component) {
   t_component->GetOutputNode(0)->SetValue(0.0f);
}


