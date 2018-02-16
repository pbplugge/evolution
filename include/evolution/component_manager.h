/** @file component_manager.h
 *  @brief Class recycles components.
 *
 *  I am not a fan of using new and delete many times during runtime.
 *  It creates memory fragmentation and invites memory leaks.
 *  This is a class to recycle components.
 *  When a new component is required, its is requested to this class.
 *  When a component is no longer used, this class is notified.
 *
 *  One statistics in thread is the total components used.
 *  If it gets higher then 10000, increase the MAX_NUMBER_OF_COMPONENTS define to a higher number.
 */
#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

namespace evolution {
   class Component;

   #define MAX_NUMBER_OF_COMPONENTS 10000

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
