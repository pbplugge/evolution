#ifndef COMPONENT_H
#define COMPONENT_H

#include "component_inputnode.h"
#include "component_outputnode.h"
#include "thread.h"

#define COMPONENT_MAX_NODES 20

namespace evolution {
   class Thread;

   /**
    * Component has input and output nodes.
    * The functionality is implemented as ComponentType.
    */
   class Component {
   public:
      Component();
      //virtual ~Component();
      void Clear(void);

      void Execute(void);

      double GetInputValue(int t_node);
      double GetOutputValue(int t_node);

      void SetOutputValue(int t_node, double v);

      void Init(ComponentType *t_component_type);
      ComponentType *GetComponentType(void);

      double GetParameterValue(int t_parameter);
      void RandomizeParameters(void);
      void RandomizeParameter(int t_parameter);
      void DisconnectFrom(Component *t_component);
      int GetInputNodeCount(void);
      int GetOutputNodeCount(void);
      ComponentInputNode *GetInputNode(int id);
      ComponentOutputNode *GetOutputNode(int output);
      void CopyFrom(Component *t_component);
      int GetNumberOfConnectedInputs(void);
      bool InputIsConnectedTo(Component *t_component);
      void Disconnect(void);
      int NumberOfInputsConnected(void);

   private:
      // Pointer to the component type in the library.
      ComponentType *m_component_type;

      // output nodes.
      ComponentOutputNode m_output_node[COMPONENT_MAX_NODES];

      // input nodes.
      ComponentInputNode m_input_node[COMPONENT_MAX_NODES];

      // parameters.
      double m_parameter[20];
   };
}

#endif
