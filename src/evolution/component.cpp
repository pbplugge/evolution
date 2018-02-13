#include "../../include/evolution.h"


using namespace evolution;

Component::Component(){
   for (int t=0; t<20; t++) {
      m_output_node[t].SetComponent(this);
      m_output_node[t].SetOutputIndex(t);
      m_input_node[t].SetComponent(this);
      m_input_node[t].SetInputIndex(t);
   }
   m_component_type = 0;
}

void Component::Clear(void){
   m_component_type = 0;
}

/**
 * Execute the component.
 */
void Component::Execute(void) {
   m_component_type->Execute(this);
}

double Component::GetInputValue(int node) {
   return m_input_node[node].GetValue();
}

double Component::GetOutputValue(int node) {
   return m_output_node[node].GetValue();
}

void Component::SetOutputValue(int node, double v) {
   m_output_node[node].SetValue(v);
}

void Component::Init(ComponentType *t_component_type) {
   m_component_type = t_component_type;

   RandomizeParameters();
}

double Component::GetParameterValue(int t_parameter) {
   return m_parameter[t_parameter];
}

ComponentType *Component::GetComponentType(void) {
   return m_component_type;
}


void Component::RandomizeParameter(int t_parameter) {
   m_parameter[t_parameter] = ((double) rand() / (RAND_MAX));
}

void Component::RandomizeParameters(void){
   for (int t=0; t<m_component_type->m_number_of_parameters; t++) {
      RandomizeParameter(t);
   }
}

/**
 * Disconnect all nodes that are connected to this component.
 */
void Component::DisconnectFrom(Component *t_component) {
   int t,t2;

   for (t=0; t<t_component->GetOutputNodeCount(); t++) {
      for (t2=0; t2<GetInputNodeCount(); t2++){
         if (m_input_node[t2].GetConnectedTo() == t_component->GetOutputNode(t)) {
            m_input_node[t2].Disconnect();
         }
      }
   }
}

/**
 * Getter for input node count.
 */
int Component::GetInputNodeCount(void) {
   return m_component_type->m_number_of_inputs;
}

/**
 * Getter for output node count.
 */
int Component::GetOutputNodeCount(void) {
   return m_component_type->m_number_of_outputs;
}


ComponentInputNode *Component::GetInputNode(int t_id) {
   if (t_id >= GetInputNodeCount()){
      //std::cout << "Component::GetInputNode() -> input_node[" << id << "] is not used by component of type " << this->component_type->name << "\n";
      exit(1);
   }
   //std::cout << id << "  "  <<  input_node_count << "\n";
   //std::cout << "Component::GetInputNode() -> " << input_node[id].GetName() << "\n";

   return &m_input_node[t_id];
}

/**
 * Getter for output node by index.
 */
ComponentOutputNode *Component::GetOutputNode(int t_id) {
   if (t_id >= GetOutputNodeCount()){
      //std::cout << "Component::GetInputNode() -> input_node[" << output << "] is not used by component of type " << this->component_type->name << "\n";
      exit(1);
   }
   return &m_output_node[t_id];
}

/**
 * This will be a copy of the given component.
 */
void Component::CopyFrom(Component *t_component) {
   int t;

   m_component_type = t_component->m_component_type;

   // Copy parameters.
   for (t = 0; t < m_component_type->m_number_of_parameters; t++) {
      m_parameter[t] = t_component->m_parameter[t];
   }
}

int Component::GetNumberOfConnectedInputs(void) {
   int c = 0;

   if (!m_component_type->m_number_of_inputs)
      return 0;

   for (int t=0; t<m_component_type->m_number_of_inputs; t++) {
      if (m_input_node[t].IsConnected()) {
         c++;
      }
   }
   return c;
}

void Component::Disconnect(void) {
   for (int t=0; t<m_component_type->m_number_of_inputs; t++) {
      m_input_node[t].Disconnect();
   }
}

/**
 * Returns true if an input is connected to the given component.
 */
bool Component::InputIsConnectedTo(Component *t_component) {
   ComponentOutputNode *n;
   for (int t=0; t<m_component_type->m_number_of_inputs; t++) {
      n = m_input_node[t].GetConnectedTo();
      if (n) {
         if (n->GetComponent() == t_component)
            return true;
      }
   }
   return false;
}

int Component::NumberOfInputsConnected(void) {
   int c = 0;

   for (int t=0; t<m_component_type->m_number_of_inputs; t++) {
      if (m_input_node[t].IsConnected())
         c++;
   }
   return c;
}
