#include <stdio.h>
#include <iostream>
#include "../../include/evolution.h"


using namespace evolution;


void ComponentOutputNode::CopyFrom(ComponentOutputNode *org) {
   output_index = org->output_index;
   name = org->name;
   value = org->value;
   type = org->type;
}

void ComponentOutputNode::Configure(int t, std::string n) {
   type = t;
   name = n;
}

void ComponentOutputNode::SetComponent(Component *c) {
   component = c;
}

Component *ComponentOutputNode::GetComponent(void) {
   return component;
}

void ComponentOutputNode::SetOutputIndex(int i) {
   output_index = i;
}

int ComponentOutputNode::GetOutputIndex(void) {
   return output_index;
}

void ComponentOutputNode::SetName(std::string n) {
   name = n;
}

std::string ComponentOutputNode::GetName(void) {
   return name;
}

void ComponentOutputNode::SetValue(double v) {
   value = v;
}

double ComponentOutputNode::GetValue(void) {
   return value;
}

void ComponentOutputNode::SetType(int t) {
   type = t;
}

int ComponentOutputNode::GetType(void) {
   return type;
}
