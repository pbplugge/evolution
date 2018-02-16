#include <stdio.h>
#include "../../include/evolution.h"


using namespace evolution;

ComponentLibrary::ComponentLibrary() {
   m_number_of_component_types = 0;
}

ComponentLibrary::~ComponentLibrary() {
   for (int t=0;t <m_number_of_component_types; t++) {
      delete m_component_type[t];
   }
}

void ComponentLibrary::AddComponentType(ComponentType *t_component_type){
   m_component_type[m_number_of_component_types] = t_component_type;
   m_number_of_component_types ++;
}

int ComponentLibrary::GetNumberOfComponentTypes(void) {
   return m_number_of_component_types;
}

ComponentType *ComponentLibrary::GetComponentType(int index) {
   return m_component_type[index];
}

