/** @file component_type.h
 *  @brief The definition of a components functionality.
 *
 *  Its a parent class for all implementations of a component you may have.
 *  It has virtual function Execute() which is called when a component executes.
 *
 *  The component type contains:
 *  - How many inputs and outputs the component has.
 *  - A definition on what type each input and output is.
 *  - The minimum and maximum number of these components should exist.
 *  - The name of the component type.
 *  - The number of parameters inside a component that can evolve.
 *
 *  TODO: Getters and setters should be implemented.
 */
#ifndef COMPONENT_TYPE_H
#define COMPONENT_TYPE_H

#include <string>


namespace evolution {
   class Thread;
   class Component;


   enum input_node_type {
      input_node_type_double,
      input_node_type_int,
      input_node_type_bool
   };

   /**
    * Represents a component type in the library.
    */
   class ComponentType {
   public:
      virtual void Execute(Component *) = 0;
      virtual ~ComponentType(){};

      int m_number_of_inputs;
      int m_number_of_outputs;

      int m_input_node_type[20];
      int m_output_node_type[20];

      std::string m_name;

      int m_max_number_of_components;
      int m_req_number_of_components;

      int m_number_of_parameters;
   };

}


#endif
