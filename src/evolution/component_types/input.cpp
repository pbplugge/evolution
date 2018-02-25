#include "../../../include/evolution.h"


using namespace evolution;


ComponentTypeInput::ComponentTypeInput() {
   m_number_of_inputs = 0;
   m_number_of_outputs = 5;
   m_number_of_parameters = 0;
   m_name = "ComponentTypeInput";
   m_input_node_type[0] = component_node_type_double;
   m_input_node_type[1] = component_node_type_double;
   m_input_node_type[2] = component_node_type_double;
   m_input_node_type[3] = component_node_type_double;
   m_input_node_type[4] = component_node_type_double;

   m_max_number_of_components = 1;
   m_req_number_of_components = 1;

}


void ComponentTypeInput::Execute(Component *t_component) {

}
