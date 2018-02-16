/** @file component_library.h
 *  @brief Contains the types of components available to an evolutionary program.
 *
 *  It should contain all available user defined component types.
 *  Look at the experiments for how it is done.
 */
#ifndef EVOLUTION_LIBRARY_H
#define EVOLUTION_LIBRARY_H

#define EVOLUTION_SYSTEM_MAX_COMPONENT_TYPES 100

namespace evolution {
   class Thread;
   class ComponentType;

   class ComponentLibrary{
   public:
      ComponentLibrary();
      ~ComponentLibrary();

      void AddComponentType(ComponentType *t_component_type);
      int GetNumberOfComponentTypes(void);
      ComponentType *GetComponentType(int index);

   private:
      ComponentType *m_component_type[EVOLUTION_SYSTEM_MAX_COMPONENT_TYPES];
      int m_number_of_component_types;
   };
}

#endif
