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

      bool m_is_terminal;
      bool m_is_primitive;

      // TODO: Getters and setters.
   };

}


#endif
