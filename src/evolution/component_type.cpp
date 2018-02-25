#include "../../include/evolution.h"


using namespace evolution;



void ComponentType::SetNumberOfInputs(int t_number_of_inputs){
   m_number_of_inputs = t_number_of_inputs;
}


int ComponentType::GetNumberOfInputs(void){
   return m_number_of_inputs;
}


void ComponentType::SetNumberOfOutputs(int t_number_of_outputs){
   m_number_of_outputs = t_number_of_outputs;
}

int ComponentType::GetNumberOfOutputs(void){
   return m_number_of_outputs;
}

void ComponentType::SetInputType(int t_index,component_node_type t_type) {
   m_input_node_type[t_index] = t_type;
}

component_node_type ComponentType::GetInputType(int t_index) {
   return m_input_node_type[t_index];
}

void ComponentType::SetOutputType(int t_index,component_node_type t_type) {
   m_output_node_type[t_index] = t_type;
}

component_node_type ComponentType::GetOutputType(int t_index) {
   return m_output_node_type[t_index];
}

void ComponentType::SetName(std::string t_name) {
   m_name = t_name;
}

std::string ComponentType::GetName(void) {
   return m_name;
}

void ComponentType::SetRequiredComponents(int t_required_components) {
   m_req_number_of_components = t_required_components;
}

int ComponentType::GetRequiredComponents(void) {
   return m_req_number_of_components;
}

void ComponentType::SetMaximumComponents(int t_maximum_components) {
   m_max_number_of_components = t_maximum_components;
}

int ComponentType::GetMaximumComponents(void) {
   return m_max_number_of_components ;
}

void ComponentType::SetNumberOfParameters(int t_number_of_parameters) {
   m_number_of_parameters = t_number_of_parameters;
}

int ComponentType::GetNumberOfParameters(void) {
   return m_number_of_parameters;
}
