/**
    checks.cpp
    Purpose: Calculates the total of 6 checks

    @author Ed Parrish
    @version 4/10/16
*/
#include <stdio.h>
#include "../../include/evolution.h"

using namespace evolution;

/**
 * Constructor.
 */
ComponentInputNode::ComponentInputNode() {
   m_connected_to = 0;
   m_component = 0;
   m_input_index = 0;
   m_type = 0;
}

/**
 * Connect the input to given output.
 */
void ComponentInputNode::ConnectTo(ComponentOutputNode *c) {
   m_connected_to = c;
}

/**
 * Disconnect to whatever it is connected to.
 */
void ComponentInputNode::Disconnect(void) {
   m_connected_to = 0;
}

/**
 * Get the output node where this input node is connected to.
 */
ComponentOutputNode *ComponentInputNode::GetConnectedTo(void) {
   return m_connected_to;
}

/**
 * Set the name for this input node.
 */
void ComponentInputNode::SetName(std::string n) {
   m_name = n;
}

/**
 * Getter for the name of this input node.
 */
std::string ComponentInputNode::GetName(void) {
   return m_name;
}

/**
 * Make json representation of this input node.
 */
std::string ComponentInputNode::ToJson(void) {
   std::string json = "{";
   if (!m_connected_to){
      json += "\"component\":\"not connected\"";
   } else {
      json += "\"component\":\"";
 //     json += connected_to->GetComponent()->GetName();
      json += "\",";
      json += "\"output\":\"";
//      json += connected_to->GetName();
      json += "\"";
   }
   json += "}";
   return json;
}

/**
 * Setter for component.
 */
void ComponentInputNode::SetComponent(Component *c) {
   m_component = c;
}

/**
 * Getter for component.
 */
Component *ComponentInputNode::GetComponent(void) {
   return m_component;
}

/**
 * Setter for input index.
 */
void ComponentInputNode::SetInputIndex(int i) {
   m_input_index = i;
}

/**
 * Getter for input index.
 */
int ComponentInputNode::GetInputIndex(void) {
   return m_input_index;
}

/**
 * Getter for type.
 */
int ComponentInputNode::GetType(void) {
   return m_type;
}

/**
 * Setter for type.
 */
void ComponentInputNode::SetType(int t) {
   m_type = t;
}

/**
 * Configure this node.
 */
void ComponentInputNode::Configure(int t, std::string n) {
   m_name = n;
   m_type = t;
   m_connected_to = 0;
}

/**
 * Get the value of the output where this input is connected to.
 */
double ComponentInputNode::GetValue(void) {
   if (!m_connected_to)
      return 0;
   return m_connected_to->GetValue();
}

/**
 * Check wether the node is connected.
 */
bool ComponentInputNode::IsConnected(void){
   if (m_connected_to)
      return true;
   return false;
}
