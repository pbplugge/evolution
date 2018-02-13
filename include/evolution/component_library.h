#ifndef EVOLUTION_LIBRARY_H
#define EVOLUTION_LIBRARY_H

#define EVOLUTION_SYSTEM_MAX_COMPONENT_TYPES 100

namespace evolution {
   class Thread;
   class ComponentType;

   /**
    * The library of components to use.
    */
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
