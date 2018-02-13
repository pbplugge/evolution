#ifndef COMPONENT_INPUTNODE_H
#define COMPONENT_INPUTNODE_H


namespace evolution {
   class ComponentOutputNode;
   class Component;
   class ComponentOutputNode;
   class EvolutionaryProgram;

   /**
    * Inputs can listen to a state or be connected to an output node.
    */
   class ComponentInputNode {
   public:
      ComponentInputNode();
      void CopyFrom(ComponentInputNode *org);
      void Configure(int type,std::string name);
      void ConnectTo(ComponentOutputNode *c);
      ComponentOutputNode *GetConnectedTo(void);
      bool IsConnected(void);
      void SetName(std::string n);
      std::string GetName(void);
      void CopyFrom(ComponentInputNode *org, EvolutionaryProgram *e);
      std::string ToJson(void);
      void FromJson(nlohmann::json json, EvolutionaryProgram *e);
      void SetComponent(Component *c);
      Component *GetComponent(void);
      void SetInputIndex(int i);
      int GetInputIndex(void);
      int GetType(void);
      void SetType(int t);
      double GetValue(void);
      void Disconnect(void);

   private:
      Component *m_component;
      ComponentOutputNode *m_connected_to;

      int m_input_index;

      std::string m_name;

      int m_type;
   };
}

#endif
