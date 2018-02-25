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
 *  - The virtual functions InitComponent() and ClearComponent() are to add/remove data to/from a component when it is created/deleted.
 *  - The virtual function ResetForNextSimulation is called when calculating fitness if necessary.
 */
#ifndef COMPONENT_TYPE_H
#define COMPONENT_TYPE_H

#include <string>


namespace evolution {
   class Thread;
   class Component;


   enum component_node_type {
      component_node_type_double,
      component_node_type_int,
      component_node_type_bool
   };

   /**
    * Represents a component type in the library.
    */
   class ComponentType {
   public:
      virtual void Execute(Component *t_component) = 0;
      virtual ~ComponentType(){};
      virtual void InitComponent(Component *t_component){}
      virtual void ClearComponent(Component *t_component){}
      virtual void ResetForNextSimulation(Component *t_component){}


      // Getters and setters.
      void SetNumberOfInputs(int t_number_of_inputs);
      int GetNumberOfInputs(void);

      void SetNumberOfOutputs(int t_number_of_outputs);
      int GetNumberOfOutputs(void);

      void SetInputType(int t_index,component_node_type t_type);
      component_node_type GetInputType(int t_index);

      void SetOutputType(int t_index,component_node_type t_type);
      component_node_type GetOutputType(int t_index);

      void SetName(std::string t_name);
      std::string GetName(void);

      void SetRequiredComponents(int t_required_components);
      int GetRequiredComponents(void);

      void SetMaximumComponents(int t_maximum_components);
      int GetMaximumComponents(void);

      void SetNumberOfParameters(int t_number_of_parameters);
      int GetNumberOfParameters(void);

   protected:

      int m_number_of_inputs;
      int m_number_of_outputs;

      component_node_type m_input_node_type[20];
      component_node_type m_output_node_type[20];

      std::string m_name;

      int m_max_number_of_components;
      int m_req_number_of_components;

      int m_number_of_parameters;
   };

}


#endif
