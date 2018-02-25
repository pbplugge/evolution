#include "../../../include/evolution.h"


using namespace evolution;





ComponentTypeOutput::ComponentTypeOutput() {
   m_number_of_inputs = 3;
   m_number_of_outputs = 0;
   m_number_of_parameters = 0;
   m_name = "ComponentTypeOutput";
   m_output_node_type[0] = component_node_type_double;
   m_output_node_type[1] = component_node_type_double;
   m_output_node_type[2] = component_node_type_double;

   m_max_number_of_components = 1;
   m_req_number_of_components = 1;
}


void ComponentTypeOutput::Execute(Component *t_component) {

}
