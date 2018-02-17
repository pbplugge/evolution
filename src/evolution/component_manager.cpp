#include <stdlib.h>     // srand, rand, abs
#include <stdio.h>      // printf
#include <math.h>       // sqrt

#include "../../include/evolution.h"

using namespace evolution;


/**
 * Construct.
 */
ComponentManager::ComponentManager() {
   m_component_count = 0;
   m_components_allocated = 0;
}

/**
 * Clean up.
 */
ComponentManager::~ComponentManager() {
   unsigned int t;

   for (t = 0; t < m_components_allocated; t++)
      delete m_component[t];
}

/**
 * Function to create a component.
 * Called from the Program.
 */
Component *ComponentManager::CreateComponent(void) {
   if (m_component_count == m_components_allocated) {
      if (m_component_count == MAX_NUMBER_OF_COMPONENTS){
         std::cout << "\nComponentManager::GetAvailableComponent() -> ERROR: Max number of " << MAX_NUMBER_OF_COMPONENTS << " components met\n";
         exit(1);
      }

      m_component[m_component_count] = new Component();
      m_component_count++;
      m_components_allocated++;
   } else {
      m_component_count++;
   }

   return m_component[m_component_count - 1];
}

/**
 * Function to destroy a component.
 * Called from the Program.
 */
void ComponentManager::DestroyComponent(Component *c) {
   unsigned int t;

   for (t = 0; t < m_component_count; t++) {
      if (m_component[t] == c) {
         c->Disconnect();

         m_component_count--;

         if (t != m_component_count) {
            m_component[t] = m_component[m_component_count];
            m_component[m_component_count] = c;
         }

         return;
      }
   }
}

/**
 * Getter for number of components.
 */
int ComponentManager::GetComponentCount(void) {
   return m_component_count;
}
