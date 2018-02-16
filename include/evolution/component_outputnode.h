/** @file component_output_node.h
 *  @brief The output node provides values that are produced by components.
 *
 *  It provides output for a component.
 *  It has no knowledge about input nodes.
 */
#ifndef COMPONENT_OUTPUT_NODE
#define COMPONENT_OUTPUT_NODE

#include <string>

namespace evolution{
   class Component;

   class ComponentOutputNode{
   public:
      void CopyFrom(ComponentOutputNode *org);
      void Configure(int type,std::string name);
      void SetComponent(Component *c);
      Component *GetComponent(void);
      void SetOutputIndex(int i);
      int GetOutputIndex(void);
      void SetName(std::string name);
      std::string GetName(void);
      void SetValue(double v);
      double GetValue(void);
      void SetType(int t);
      int GetType(void);

   private:
      Component *component;
      int output_index;
      std::string name;
      double value;
      int type;
   };
}


#endif
