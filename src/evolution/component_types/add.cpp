#include "../../../include/evolution.h"


using namespace evolution;


ComponentTypeAdd::ComponentTypeAdd() {
   m_number_of_inputs = 2;
   m_number_of_outputs = 1;
   m_number_of_parameters = 0;
   m_name = "ComponentTypeAdd";
   m_input_node_type[0] = component_node_type_double;
   m_input_node_type[1] = component_node_type_double;
   m_output_node_type[0] = component_node_type_double;

   m_max_number_of_components = 1;
   m_req_number_of_components = 1;
}


void ComponentTypeAdd::Execute(Component *t_component) {
   double v1 = t_component->GetInputValue(0);
   double v2 = t_component->GetInputValue(1);

   std::cout << "ComponentTypeAdd::Execute() -> Adding " << v1 << " and " << v2 << ".\n";

   t_component->SetOutputValue(0,v1+v2);
}
