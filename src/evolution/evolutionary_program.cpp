#include "../../include/evolution.h"

using namespace evolution;


EvolutionaryProgram::EvolutionaryProgram() {
   m_component_manager = 0;
   m_component_count = 0;
   m_component_library = 0;
}


void EvolutionaryProgram::SetComponentManager(ComponentManager *t_component_manager) {
   m_component_manager = t_component_manager;
}

void EvolutionaryProgram::SetComponentLibrary(ComponentLibrary *t_component_library) {
   m_component_library = t_component_library;
}

/**
 * Reset Destroys existing components and adds new required components.
 */
void EvolutionaryProgram::Reset(void) {
   Cleanup();
   CorrectComponentTypeAmounts();
}

/**
 * Cleanup removes existing components.
 */
void EvolutionaryProgram::Cleanup(void) {
   while (m_component_count > 0) {
      RemoveComponent(m_component_count-1);
   }
}

/**
 * Remove a component of a given type.
 */
void EvolutionaryProgram::RemoveComponentOfType(ComponentType *t_type) {
   for (int t=0; t < m_component_count; t++) {
      if (m_component[t]->GetComponentType() == t_type) {
         RemoveComponent(t);
         return;
      }
   }
}

/**
 * Remove component.
 */
void EvolutionaryProgram::RemoveComponent(int t_index) {
   Component *c = m_component[t_index];
   int r;

   if (t_index >= m_component_count) {
      std::cout << "EvolutionaryProgram::RemoveComponent() -> Error: t_index (" << t_index << ") should be lower then m_component_count (" << m_component_count << ")\n";
      exit(1);
   }

   if (m_component_count > 1) {
      // Disconnect from all inputs.
      for (r = 0; r < m_component_count; r++) {
         m_component[r]->DisconnectFrom(c);
      }

      c->Disconnect();

      m_component[t_index] = 0;

      // Remove component but keep the order of components.
      for (r = t_index; r < m_component_count - 1; r++) {
         m_component[r] = m_component[r + 1];
      }
   }

   c->GetComponentType()->ClearComponent(c);
   m_component_manager->DestroyComponent(c);

   m_component_count--;
}

/**
 * Remove component.
 */
void EvolutionaryProgram::RemoveComponent(Component *t_component){
   int t;

   for (t = 0; t < m_component_count; t++) {
      if (t_component == m_component[t]) {
         RemoveComponent(t);
         return;
      }
   }
}

/**
 * Try to remove random component 10 times.
 */
void EvolutionaryProgram::RemoveRandomComponent(void) {
   if (m_component_count < 2)
      return;

   int t, r;

   for (t = 0; t < 10; t++) {
      r = rand() % m_component_count;

      Component *c = m_component[r];
      ComponentType *ct = c->GetComponentType();

      // Check if we have the number of components required before removal.
      if (ct->GetRequiredComponents() != ct->GetMaximumComponents() &&
         NumberOfComponentsOfType(ct) > ct->GetRequiredComponents()) {
         RemoveComponent(r);
         return;
      }
   }
}

/**
 * Either:
 * - add a component with connections
 * - remove a component with connections.
 * - add or remove a connection.
 * - Order components on dependency.
 * - Flip 2 components.
 * - Shuffle and re-connect the components.
 * TODO: put mutation chances in configuration.?
 */
void EvolutionaryProgram::MutateStructure(void) {
   int r = rand() % 7;

   //std::cout << "mutate structure "<< r << "\n";

   switch (r) {
   case 0:  // Add random component.
      AddRandomComponent();
      break;
   case 1:  // Remove random component.
      RemoveRandomComponent();
      break;
   case 2:  // Add random connection.
      ConnectRandomNodes();
      break;
   case 3:  // Remove random connection.
      DisconnectRandomNodes();
      break;
   case 4:
      OrderComponentsOnDependency();
      break;
   case 5:
      FlipTwoRandomComponents();
      break;
   case 6:
      ShuffleAndReconnect();
   }
}

void EvolutionaryProgram::FlipTwoRandomComponents(void) {
   int c1 = rand() % m_component_count;
   int c2 = rand() % m_component_count;
   FlipComponentPositions(c1,c2);
}

void EvolutionaryProgram::FlipComponentPositions(int t_pos1, int t_pos2) {
   if (t_pos1 == t_pos2)
      return;

   Component *c = m_component[t_pos1];
   m_component[t_pos1] = m_component[t_pos2];
   m_component[t_pos2] = c;
}

/**
 * On execution the last component is executed first.
 * We need to execute the components without input first.
 * After that the components that depend on that and so on.
 */
void EvolutionaryProgram::OrderComponentsOnDependency(void) {
   int t,t2,attempts = 0;
   bool sorted = false;

   while (!sorted && attempts < 10) {
      attempts ++;
      sorted = true;

      // Place components depending on the components before.
      // The inputs of earlier components should be connected to the outputs of later components.
      // If its the other way around flip them.
      for (t=0; t<m_component_count-1 ; t++) {
         for (t2=t+1; t2<m_component_count ; t2++) {
            if (m_component[t2]->InputIsConnectedTo(m_component[t])) {
               FlipComponentPositions(t2,t);
               sorted = false;
            }
         }
      }
   }
}

/**
 * Shuffles all components and reconnects them randomly.
 */
void EvolutionaryProgram::ShuffleAndReconnect(void) {
   int t;

   DisconnectAll();

   for (t=0; t<10; t++) {
      FlipTwoRandomComponents();
   }

   for (t=0; t<10; t++) {
      AddRandomConnection();
   }
}

void EvolutionaryProgram::DisconnectAll(void) {
   for (int t=0; t<m_component_count; t++) {
      m_component[t]->Disconnect();
   }
}

/**
 * Find a component with parameters and change it.
 */
void EvolutionaryProgram::MutateParameters(void) {
   int t,p;

   for (t=0; t<m_component_count; t++) {
      p = m_component[t]->GetComponentType()->GetNumberOfParameters();
      if (p > 0) {
         m_component[t]->RandomizeParameter(rand() % p);
      }
   }
}

/**
 * Returns a random component of type t_type.
 */
Component *EvolutionaryProgram::GetRandomComponentOfType(ComponentType *t_type) {
   int t, c=0, r, n = NumberOfComponentsOfType(t_type);
   if (!n) {
      return 0;
   }

   r = rand() % n;
   for (t=0; t<m_component_count; t++) {
      if (m_component[t]->GetComponentType() == t_type) {
         if (r == c) {
            return m_component[t];
         } else {
            c++;
         }
      }
   }

   return 0;
}

/**
 * Removes components on inputs of given component recursively.
 */
void EvolutionaryProgram::RemoveComponentOnInputsRecursively(Component *t_component,bool t_remove) {
   for (int t=0; t < m_component_count; t++) {
      if (t_component->InputIsConnectedTo(m_component[t])) {
         // Disconnect first to prevent an infinite loop.
         t_component->DisconnectFrom(m_component[t]);

         // Do the recursive part.
         RemoveComponentOnInputsRecursively(m_component[t],true);

         // Remove the component.
         if (t_remove) {
            RemoveComponent(t_component);
         }
      }
   }
}

/**
 * Take parts of both parents and combine.
 * First copy from parent 1, then match one component and copy that one down from parent 2.
 */
void EvolutionaryProgram::Crossover(EvolutionaryProgram *t_parent1, EvolutionaryProgram *t_parent2){
   int t,r;
   Component *c;

   if (!t_parent1->GetComponentCount()) {
      std::cout << "EvolutionaryProgram::Crossover() -> Error: parent 1 has no components.\n";
      exit(0);
   }
   if (!t_parent2->GetComponentCount()) {
      std::cout << "EvolutionaryProgram::Crossover() -> Error: parent 2 has no components.\n";
      exit(0);
   }

   // First make this equal to parent 1.
   CopyFrom(t_parent1);

   // Pick one component that is the same type. 10 attempts.
   for (t=0; t<10; t++) {
      r = rand() % m_component_count;

      // Get component in parent 2's system of the same type.
      c = t_parent2->GetRandomComponentOfType(m_component[r]->GetComponentType());
      if (c) {
         // Remove inputs of my component recursively but not this component (t_remove = false)
         //RemoveComponentOnInputsRecursively(m_component[r],false);

         std::cout << "EvolutionaryProgram::Crossover() on type: " << c->GetComponentType()->GetName() << " " << r << ", " << t_parent2->GetComponentIndex(c) << "\n";

         // Append inputs of parent 2's components recursively.
         CopyComponentOnInputsRecursively(t_parent2, r, t_parent2->GetComponentIndex(c));

         // Now sort this.
         OrderComponentsOnDependency();
         t = 10;
      }
   }

   if (!m_component_count) {
      std::cout << "EvolutionaryProgram::Crossover() -> Error: child has no components, parent components: " << t_parent1->GetComponentCount() << " and " << t_parent2->GetComponentCount() << ".\n";
      exit(0);
   }

   // Make sure the required components are there since they may be removed in the crossover.
   CorrectComponentTypeAmounts();
}

/**
 * Executes all components from last till first.
 * This is logical because last added component supplement the existing program.
 */
void EvolutionaryProgram::Execute(void) {
   // Components added last should be executed first.
   for (int t=m_component_count-1; t>=0; t--) {
      m_component[t]->Execute();
   }
}

void EvolutionaryProgram::Randomize(void) {
   Reset();
   AddRandomComponents(5);
   ShuffleAndReconnect();
   //AddRandomConnections();
   //OrderComponentsOnDependency();
}

/**
 * Make sure the required components are there and the maximum is not exceded.
 */
void EvolutionaryProgram::CorrectComponentTypeAmounts(void) {
   int t,t2;
   ComponentType *type;

   for (t=0; t<m_component_library->GetNumberOfComponentTypes(); t++) {
      type = m_component_library->GetComponentType(t);
      if (type->GetRequiredComponents() > 0) {
         // Add the ones that where not there.
         for (t2 = NumberOfComponentsOfType(type); t2 < type->GetRequiredComponents(); t2++) {
            AddComponent(type);
         }
         for (;t2 > type->GetMaximumComponents(); t2--) {
            RemoveComponentOfType(type);
         }
      }
   }
}

void EvolutionaryProgram::AddRandomComponents(int t_number_of_components) {
   for (int t=0; t<t_number_of_components; t++) {
      AddRandomComponent();
   }
}

int EvolutionaryProgram::NumberOfComponentsOfType(ComponentType *t_type) {
   int total = 0;
   for (int t = 0; t < m_component_count; t++) {
      if (m_component[t]->GetComponentType() == t_type) {
         total++;
      }
   }
   return total;
}

/**
 * Returns true if the maximum number of components of given type is met.
 */
bool EvolutionaryProgram::MaxNumberOfComponentsMet(ComponentType *t_type) {
   if (NumberOfComponentsOfType(t_type) >= t_type->GetMaximumComponents())
      return true;
   return false;
}


Component *EvolutionaryProgram::AddRandomComponent(void) {
   int t;

   if (!m_component_library->GetNumberOfComponentTypes()) {
      std::cout << "EvolutionaryProgram::AddRandomComponent() -> ERROR: There are no components in the library\n";
      return 0;
   }

   // 40 attempts to find a component.
   for (t = 0; t < 40; t++) {
      ComponentType *ct =  m_component_library->GetComponentType(rand() % m_component_library->GetNumberOfComponentTypes());
      if (ct->GetRequiredComponents() != ct->GetMaximumComponents() &&
            !MaxNumberOfComponentsMet(ct)) {
         return AddComponent(ct);
      }
   }

   return 0;
}

/**
 * Create the component. That is, request one from the component manager.
 */
Component *EvolutionaryProgram::CreateComponent(void) {
   m_component[m_component_count] = m_component_manager->CreateComponent();
   if (!m_component[m_component_count]) {
      std::cout << "EvolutionaryProgram::CreateComponent() -> Error: No component available.\n";
      exit(1);
   }
   m_component_count ++;
   return m_component[m_component_count-1];
}

Component *EvolutionaryProgram::AddComponent(ComponentType *t_component_type) {
   Component *c = CreateComponent();
   if (c)      c->Init(t_component_type);
   return c;
}

/**
 * Add some random connections.
 */
void EvolutionaryProgram::AddRandomConnections(void) {
   for (int t=0; t<10; t++) {
      AddRandomConnection();
   }
}

void EvolutionaryProgram::AddRandomConnections(Component *t_component) {
   if (!t_component || m_component_count <= 1)
      return;

   ComponentType *type = t_component->GetComponentType();
   int inputs = GetInputNodeCount();
   int outputs = GetOutputNodeCount();
   ComponentInputNode *in;
   ComponentOutputNode *on;
   int t,t2;

   // Connect its inputs.
   for (t=0; t<type->GetNumberOfInputs(); t++) {
      in = t_component->GetInputNode(t);
      for (t2=0; t2<10; t2++) {
         on = GetOutputNode(rand() % outputs);
         if (on && on->GetType() == in->GetType() && on->GetComponent() != in->GetComponent()) {
            in->ConnectTo(on);
            t2 = 10;
         }
      }
   }

   // Connect its outputs.
   for (t=0; t<type->GetNumberOfInputs(); t++) {
      on = t_component->GetOutputNode(t);
      for (t2=0; t2<10; t2++) {
         in = GetInputNode(rand() % inputs);
         if (in && on->GetType() == in->GetType() && on->GetComponent() != in->GetComponent()) {
            in->ConnectTo(on);
            t2 = 10;
         }
      }
   }
}

/**
 * Do some attempts to connect an available input node to an output node.
 * The outputs must be components that earlier.
 */
void EvolutionaryProgram::AddRandomConnection(void) {
   int inputs = GetInputNodeCount();
   int outputs = GetOutputNodeCount();
   ComponentInputNode *in;
   ComponentOutputNode *on;
   int t,t2;
   int in_index,out_index;
   int in_component_index,on_component_index;

   if (!inputs || !outputs)
      return;

   for (t=0; t<10; t++) {
      in_index = rand() % inputs;
      in = GetInputNode(in_index);
      if (in && !in->IsConnected()) {
         in_component_index = GetComponentIndex(in->GetComponent());

         for (t2=0; t2<10; t2++) {
            out_index = rand() % outputs;

            on = GetOutputNode(out_index);
            if (on) {
               on_component_index = GetComponentIndex(on->GetComponent());
               if (on->GetType() == in->GetType() &&
                   on->GetComponent() != in->GetComponent() &&
                   on_component_index > in_component_index) {
                  //std::cout << "EvolutionaryProgram::AddRandomConnection() -> Connecting output component " << on_component_index << " to input component index " << in_component_index << "\n";
                  in->ConnectTo(on);
                  return;
               }
            }
         }
      }
   }
}


/**
 * If exists return the first component of type t_component_type. Otherwise return 0.
 */
Component *EvolutionaryProgram::GetComponentOfType(ComponentType *t_component_type) {
   for (int t=0; t<m_component_count; t++) {
      if (m_component[t]->GetComponentType() == t_component_type)
         return m_component[t];
   }

   return 0;
}

/**
 * Connect an input to an output of the same type.
 * If the input was already connected, do it anyhow.
 * Try 10 times to find a node to connect to.
 */
void EvolutionaryProgram::ConnectRandomNodes(void) {
   int ic = GetInputNodeCount();
   int oc = GetOutputNodeCount();
   int tries = 0;
   int inode,onode;

   // If there is nothing to connect just return.
   if (!ic || !oc)
      return;

   inode = rand() % ic;

   //std::cout << "EvolutionaryProgram::ConnectRandomNodes() -> node: " << inode << "\n";
   ComponentInputNode *in = GetInputNode(inode);
   ComponentOutputNode *out;

   // Could not find input node.
   if (!in) {
      std::cout << "EvolutionaryProgram::ConnectRandomNodes() -> Could not get input node " << inode << " / " <<  ic << ".\n";
      return;
   }

   //std::cout << "EvolutionaryProgram::ConnectRandomNodes() -> oc: " << oc << "\n";

   for (tries = 0; tries < 10; tries++) {
      //std::cout << "EvolutionaryProgram::ConnectRandomNodes() -> tries " << tries << "\n";

      onode = rand() % oc;
      //std::cout << "EvolutionaryProgram::ConnectRandomNodes() -> onode " << onode << "\n";
      out = GetOutputNode(onode);
      if (out) {
         if (out->GetType() == in->GetType()) {
            in->ConnectTo(out);
            return;
         }
      } else {
         std::cout << "EvolutionaryProgram::ConnectRandomNodes() -> Could not get output node " << onode << " / " << oc << ".\n";
      }
   }
}

/**
 * Disconnect a random existing connection.
 */
void EvolutionaryProgram::DisconnectRandomNodes(void) {
   int ic = GetInputNodeCount();

   if (!ic)
      return;

   ComponentInputNode *in = GetInputNode(rand() % (ic - 1));
   if (!in) {
      std::cout << "EvolutionaryProgram::DisconnectRandomNodes() -> There are inputs but none found.\n";
      return;
   }

   in->Disconnect();
}

/**
 * Returns the number of inputs in the system.
 */
int EvolutionaryProgram::GetInputNodeCount(void) {
   int t, c = 0;

   for (t = 0; t < m_component_count; t++) {
      c += m_component[t]->GetInputNodeCount();
   }
   return c;
}

/**
 * Returns the number of outputs in the system.
 */
int EvolutionaryProgram::GetOutputNodeCount(void) {
   int t, c = 0;

   for (t = 0; t < m_component_count; t++) {
      c += m_component[t]->GetOutputNodeCount();
   }
   return c;
}

/**
 * Get the n'th input node in the program.
 */
ComponentInputNode *EvolutionaryProgram::GetInputNode(int n) {
   int t, c = 0;

   for (t = 0; t < m_component_count; t++) {
      if (n >= c && n < c + m_component[t]->GetInputNodeCount()) {
         return m_component[t]->GetInputNode(n - c);
      }
      c += m_component[t]->GetInputNodeCount();
   }
   return 0;
}

/**
 * Get the n'th output node in the program.
 */
ComponentOutputNode *EvolutionaryProgram::GetOutputNode(int n) {
   int t, c = 0;

   for (t = 0; t < m_component_count; t++) {
      if (n >= c && n < c + m_component[t]->GetOutputNodeCount()) {
         return m_component[t]->GetOutputNode(n - c);
      }
      c += m_component[t]->GetOutputNodeCount();
   }
   return 0;
}

/**
 * Returns component at given index.
 */
Component *EvolutionaryProgram::GetComponentAt(int t_index) {
   return m_component[t_index];
}

/**
 * Opposite of previous.
 * If component was not found, return -1.
 */
int EvolutionaryProgram::GetComponentIndex(Component *t_component) {
   for (int t=0; t<m_component_count; t++) {
      if (m_component[t] == t_component)
         return t;
   }
   return -1;
}

/**
 * Copy this evolutionary system from another.
 */
void EvolutionaryProgram::CopyFrom(EvolutionaryProgram *t_evolutionary_program) {
   int t,t2,i;
   Component *corg;
   ComponentType *ct;
   ComponentOutputNode *on;
   EvolutionaryProgram *_this = this;

   if (!_this) {
      std::cout << "EvolutionaryProgram::CopyFrom() -> Error no this.\n";
      exit(1);
   }
   if (!t_evolutionary_program) {
      std::cout << "EvolutionaryProgram::CopyFrom() -> Error no orig.\n";
      exit(1);
   }

   // Clean up existing data.
   Cleanup();

   m_component_count = t_evolutionary_program->m_component_count;

   // Create a copy of the components.
   for (t = 0; t < m_component_count; t++) {
      corg = t_evolutionary_program->GetComponentAt(t);
      m_component[t] = m_component_manager->CreateComponent();
      if (!m_component[t]) {
         std::cout << "EvolutionaryProgram::CopyFrom() -> ERROR: no new component received.!\n";
         exit(1);
      }
      m_component[t]->CopyFrom(t_evolutionary_program->m_component[t]);
   }

   // Connect the components in the same way.
   for (t = 0; t < m_component_count; t++) {
      corg = t_evolutionary_program->m_component[t];
      ct = corg->GetComponentType();
      for (t2=0; t2 < ct->GetNumberOfInputs(); t2++) {
         on = corg->GetInputNode(t2)->GetConnectedTo();
         if (on) {
            // get index of component.
            i = t_evolutionary_program->GetComponentIndex(on->GetComponent());

            // Get same node in this program.
            on = m_component[i]->GetOutputNode(on->GetOutputIndex());

            m_component[t]->GetInputNode(t2)->ConnectTo(on);
         } else {
            // else its not connected.
            m_component[t]->GetInputNode(t2)->Disconnect();
         }
      }
   }
}

/**
 * Copies all input on a given component recursively from another program.
 * t_index is index of the destination component in this EvolutionaryProgram.
 * t_ep_index is the index of the source component in the other EvolutionaryProgram.
 * So the components on both indexes should be of the same type.
 * The best thing i come up with is copying all after t_ep_index and then remove unconnected components.
 *
 * TODO: does not check on maximum allowed components of one type.
 */
void EvolutionaryProgram::CopyComponentOnInputsRecursively(EvolutionaryProgram *t_ep, int t_index, int t_ep_index) {
   int t,t2,on_source_index,on_my_index,source_component_index,my_component_index;
   Component *nc;
   Component *corg;
   ComponentType *ct;
   ComponentOutputNode *on;
   EvolutionaryProgram *_this = this;

   //std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> start: my index " << t_index << " other index: " << t_ep_index << "\n";

   // this must exist.
   if (!_this) {
      std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> Error: no this.\n";
      exit(1);
   }
   // If parent must exist.
   if (!t_ep) {
      std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> Error: no parent.\n";
      exit(1);
   }
   // Check if both components are of the same type.
   if (t_ep->m_component[t_ep_index]->GetComponentType() != m_component[t_index]->GetComponentType()){
      std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> Components are of different types.\n";
      exit(1);
   }

   // Remove existing components after t_index.
   while (m_component_count > t_index+1) {
      std::cout << "removing component: " << (m_component_count-1) << "\n";
      RemoveComponent(m_component_count-1);
   }

   // Create a copy of the components.
   for (t = t_ep_index+1; t < t_ep->m_component_count; t++) {
      Component *c = t_ep->m_component[t];
      if (c) {
         nc = CreateComponent();
         nc->CopyFrom(c);

         on_my_index = m_component_count - 1;

         std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> my index / other index: " << on_my_index << " / " << t << "\n";
         //std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> ctypes: " << m_component[on_my_index]->GetComponentType()->GetName() << " / " << t_ep->m_component[t]->GetComponentType()->GetName() << "\n";

      } else {
         std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> Error: no component received.\n";
         exit(1);
      }
   }

   // Connect the components in the same way.
   for (source_component_index = t_ep_index; source_component_index < t_ep->m_component_count; source_component_index++) {
      corg = t_ep->m_component[source_component_index];
      ct = corg->GetComponentType();
      my_component_index = m_component_count - (t_ep->m_component_count - source_component_index);
      for (t2=0; t2 < ct->GetNumberOfInputs(); t2++) {
         on = corg->GetInputNode(t2)->GetConnectedTo();

         if (on) {
            // get index of output node component in source program.
            on_source_index = t_ep->GetComponentIndex(on->GetComponent());

            //std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> output node " << on->GetOutputIndex() << " of component " << t_ep->m_component[on_source_index]->GetComponentType()->GetName() << " connected to input node " << t2 << " of component " << corg->GetComponentType()->GetName() << "\n";

            if (on_source_index >= t_ep_index) {
               // Get same component in this program.
               on_my_index = m_component_count - (t_ep->m_component_count - on_source_index);

               //std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> types should be the same: " << m_component[my_component_index]->GetComponentType()->GetName() << " / " << t_ep->m_component[source_component_index]->GetComponentType()->GetName() << "\n";
               //std::cout << "EvolutionaryProgram::CopyComponentOnInputsRecursively() -> types should be the same: " << m_component[on_my_index]->GetComponentType()->GetName() << " / " << t_ep->m_component[on_source_index]->GetComponentType()->GetName() << "\n";


               // Get same node in this program.
               on = m_component[on_my_index]->GetOutputNode(on->GetOutputIndex());
               m_component[my_component_index]->GetInputNode(t2)->ConnectTo(on);
            }
         } else {
            // Just make sure its not connected.
            m_component[my_component_index]->GetInputNode(t2)->Disconnect();
         }
      }
   }

   // Correct if too many or too few components of some type.
   CorrectComponentTypeAmounts();
}


int EvolutionaryProgram::GetComponentCount(void) {
   return m_component_count;
}

/**
 * outputs all information to std::cout
 */
void EvolutionaryProgram::Debug(void) {
   int t,t2;
   std::cout << "EvolutionaryProgram::Debug() -> " << m_component_count << " components:\n";
   ComponentInputNode *in;
   ComponentOutputNode *on;
   ComponentType *type;

   for (t=0; t<m_component_count; t++) {
      type = m_component[t]->GetComponentType();
      std::cout << "EvolutionaryProgram::Debug() -> component[" << t << "] of type '"<< type->GetName() << "': " << type->GetNumberOfInputs() << " input nodes\n";
      for (t2 = 0; t2 < type->GetNumberOfInputs(); t2++) {
         in = m_component[t]->GetInputNode(t2);
         if (!in->IsConnected()) std::cout << t <<"[" << t2 << "] <- nc\n";
         else {
            on = in->GetConnectedTo();
            std::cout << t << "[" << t2 << "] <- " << GetComponentIndex(on->GetComponent()) << "[" << on->GetOutputIndex() << "]\n";
         }
      }
   }
}

/**
 * Created to use in python networkx.
 * https://networkx.github.io/documentation/networkx-1.10/reference/readwrite.json_graph.html
 *
 * They give this as an example:
 * https://bl.ocks.org/mbostock/4062045
 *
 * I had to add more information to be able to reconstruct the program from the json later on.
 */
std::string EvolutionaryProgram::ToJson(void) {
   ComponentType *type;
   ComponentInputNode *in;
   ComponentOutputNode *on;
   int t,t2;
   bool comma = false;

   std::string j = "{\"nodes\": [";

   for (t=0; t<m_component_count; t++) {
      if (t>0) j += ",";
      type = m_component[t]->GetComponentType();
      j += "{\"id\":\"" + std::to_string(t) + "\",";
      j += "\"group\":\"" + std::string(type->GetName()) + "\",";
      j += "\"parameters\":[";
      for (t2=0; t2<type->GetNumberOfParameters(); t2++) {
         if (t2>0) j += ",";
         j += std::to_string(m_component[t]->GetParameterValue(t2));
      }
      j += "]}";
   }

   j += "],\"links\": [";

   for (t=m_component_count-1; t >= 0; t--) {
      type = m_component[t]->GetComponentType();
      for (t2=0; t2 < type->GetNumberOfInputs(); t2++) {
         in = m_component[t]->GetInputNode(t2);
         if (in->IsConnected()) {
            on = in->GetConnectedTo();
            if (comma)          j += ",";
            else                comma = true;
            j += "{\"source\":\"" + std::to_string(GetComponentIndex(on->GetComponent())) + "\",";
            j += "\"target\":\"" + std::to_string(GetComponentIndex(in->GetComponent())) + "\",";
            j += "\"sourcenode\":" + std::to_string(on->GetOutputIndex()) + ",";
            j += "\"targetnode\":" +  std::to_string(in->GetInputIndex()) + "}";
         }
      }
   }

   j += "]}";

   return j;
}

/**
 * TODO.
 */
void EvolutionaryProgram::FromJson(std::string json) {

}


void EvolutionaryProgram::ResetComponentsForNextSimulation(void) {
   int t;
   ComponentType *type;
   for (t=0; t<m_component_count; t++) {
      type = m_component[t]->GetComponentType();
      type->ResetForNextSimulation(m_component[t]);
   }
}
