#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

namespace evolution {
   class Component;

   #define MAX_NUMBER_OF_COMPONENTS 10000

   /**
    * Class recycles components.
    */
   class ComponentManager{
   public:
      ComponentManager(void);
      ~ComponentManager(void);

      Component *CreateComponent(void);
      void DestroyComponent(Component *c);
      int GetComponentCount(void);

   private:
      Component *m_component[MAX_NUMBER_OF_COMPONENTS];
      unsigned int m_component_count;
      unsigned int m_components_allocated;
   };

}

#endif
