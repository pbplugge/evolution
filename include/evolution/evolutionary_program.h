/** @file evolutionary_program.h
 *  @brief A single evolutionary program inside an individual.
 *
 *  It is responsible for connecting a random selection of (user defined) components from the component library and its mutations and cross-overs.
 *  It does not know anything about what it is used for, its just the wiring and execution.
 */
#ifndef EVOLUTIONARY_PROGRAM_H
#define EVOLUTIONARY_PROGRAM_H



#define PROGRAM_MAX_COMPONENTS 1000

namespace evolution {
   class Component;
   class ComponentManager;

   class EvolutionaryProgram {
   public:
      EvolutionaryProgram();

      void SetComponentManager(ComponentManager *t_component_manager);
      void SetComponentLibrary(ComponentLibrary *t_component_library);
      void CopyFrom(EvolutionaryProgram *t_evolutionary_program);
      void Cleanup(void);

      void MutateStructure(void);
      void MutateParameters(void);
      void Crossover(EvolutionaryProgram *t_parent1, EvolutionaryProgram *t_parent2);
      void Randomize(void);

      Component *GetComponentOfType(ComponentType *t_component_type);
      int GetComponentCount(void);
      Component *GetComponentAt(int index);


      void Execute(void);

      void Debug(void);

      std::string ToJson(void);
      void FromJson(std::string json);

      // Evolution actions.
      void ShuffleAndReconnect(void);
      void AddRandomConnections(Component *t_component);
      void AddRandomConnections(void);
      void AddRandomConnection(void);
      void RemoveRandomComponent(void);
      void ConnectRandomNodes(void);
      void FlipTwoRandomComponents(void);
      void DisconnectRandomNodes(void);
      Component *AddRandomComponent(void);
      void ResetComponentsForNextSimulation(void);

   private:
      ComponentManager *m_component_manager;
      ComponentLibrary *m_component_library;
      Component *m_component[PROGRAM_MAX_COMPONENTS];
      int m_component_count;

      void Reset(void);

      // Components.
      void CorrectComponentTypeAmounts(void);
      void AddRandomComponents(int t_number_of_components);
      Component *AddComponent(ComponentType *t_component_type);
      Component *CreateComponent(void);
      void OrderComponentsOnDependency(void);


      // Other tools.
      bool MaxNumberOfComponentsMet(ComponentType *t_type);
      int NumberOfComponentsOfType(ComponentType *t_type);
      void RemoveComponent(int t_index);
      void RemoveComponentOfType(ComponentType *t_type);
      void RemoveComponent(Component *t_component);
      void DisconnectAll(void);
      int GetInputNodeCount(void);
      int GetOutputNodeCount(void);
      ComponentInputNode *GetInputNode(int n);
      ComponentOutputNode *GetOutputNode(int n);
      int GetComponentIndex(Component *t_component);
      void FlipComponentPositions(int t_pos1, int t_pos2);
      Component *GetRandomComponentOfType(ComponentType *t_type);
      void RemoveComponentOnInputsRecursively(Component *t_component,bool t_remove);
      void CopyComponentOnInputsRecursively(EvolutionaryProgram *t_ep, int t_index, int t_ep_index);
   };
}

#endif
