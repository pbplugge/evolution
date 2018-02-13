#include <stdio.h>
#include <iostream>
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
 * Copy this input node from given other input node.
 */
/*void ComponentInputNode::CopyFrom(ComponentInputNode *org, EvolutionaryProgram *e) {
   name = org->name;
   //event_id = org->event_id;
   type = org->type;

   if (!org) {
      std::cout << "ComponentInputNode::CopyFrom() -> Error: no org node.\n";
      exit(1);
   }
   if (!e) {
      std::cout << "ComponentInputNode::CopyFrom() -> Error: no evolution system provided.\n";
      exit(1);
   }

   if (org->connected_to) {
      Component *c = e->GetComponent(org->connected_to->GetComponent()->GetName());
      if (!c) {
         std::cout << "ComponentInputNode::CopyFrom() -> Error: could not get component: " << org->connected_to->GetComponent()->GetName() << "\n";
         std::cout << "ComponentInputNode::CopyFrom() -> Component type: " << component->GetComponentType()->name << "\n";
         std::cout << "ComponentInputNode::CopyFrom() -> input index: " << input_index << "\n";
         std::cout << "ComponentInputNode::CopyFrom() -> node target type: " << org->connected_to->GetComponent()->GetComponentType()->name << "\n";
         exit(1);
      }
      connected_to = c->GetOutputNode(org->connected_to->GetName());
      if (!connected_to) {
         std::cout << "ComponentInputNode::CopyFrom() -> Error: could not get node " << org->connected_to->GetName() << " of component " << org->connected_to->GetComponent()->GetName() << "\n";
         exit(1);
      }
   } else {
      connected_to = 0;
   }
}*/

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
 * Node from json.
 */
//void ComponentInputNode::FromJson(nlohmann::json json, EvolutionaryProgram *e){
/*
   std::string cmp = json["component"].get<std::string>();
   if (cmp == "not connected"){
      connected_to = 0;
      return;
   }

   Component *c = e->GetComponent(cmp);
   if (!c) {
      std::cout << "ComponentInputNode::FromJson() -> Error: could not get component: " << cmp << "\n";
      std::cout << "ComponentInputNode::FromJson() -> Component type: " << component->GetComponentType()->name << "\n";
      std::cout << "ComponentInputNode::FromJson() -> input index: " << input_index << "\n";
      exit(1);
   }

   std::string out = json["output"].get<std::string>();

   connected_to = c->GetOutputNode(out);
   if (!connected_to) {
      std::cout << "ComponentInputNode::FromJson() -> Error: could not get node " << out << " of component " << cmp << "\n";
      exit(1);
   }
*/
//}

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
   //event_id
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
