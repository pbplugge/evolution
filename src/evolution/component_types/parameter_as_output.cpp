#include "../../../include/evolution.h"


using namespace evolution;



ComponentTypeParameterAsOutput::ComponentTypeParameterAsOutput(){
   m_number_of_inputs = 0;
   m_number_of_outputs = 1;
   m_number_of_parameters = 1;
   m_name = "ComponentTypeParameterAsOutput";
   m_output_node_type[0] = component_node_type_double;

   m_max_number_of_components = 2;
   m_req_number_of_components = 2;
}

void ComponentTypeParameterAsOutput::Execute(Component *t_component){
   double v = t_component->GetParameterValue(0);

   std::cout << "ComponentTypeParameterAsOutput::Execute() -> " << v << "\n";
   t_component->SetOutputValue(0,v);
}
