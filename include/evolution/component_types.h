/** @file component_types.h
 *  @brief All component types that are already implemented.
 *
 *  implemented in ~/src/evolution/component_types/<name>.cpp
 */
#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H


#include "component_type.h"


namespace evolution {


   class ComponentTypeAdd:public ComponentType {
   public:
      ComponentTypeAdd();
      void Execute(Component *t_component);
   };


   class ComponentTypeMemory:public ComponentType {
   public:
      ComponentTypeMemory();
      void Execute(Component *t_component);
   };


   class ComponentTypeThreshold:public ComponentType {
   public:
      ComponentTypeThreshold();
      void Execute(Component *t_component);
      void ResetForNextSimulation(Component *t_component);
   };


   class ComponentTypeChangeDetector:public ComponentType {
   public:
      ComponentTypeChangeDetector();
      void Execute(Component *t_component);
      void ResetForNextSimulation(Component *t_component);
   };


   class ComponentTypeInput:public ComponentType {
   public:
      ComponentTypeInput();
      void Execute(Component *t_component);
   };


   class ComponentTypeOutput:public ComponentType {
   public:
      ComponentTypeOutput();
      void Execute(Component *t_component);
   };


   class ComponentTypeCounter:public ComponentType {
   public:
      ComponentTypeCounter();
      void Execute(Component *t_component);
      void ResetForNextSimulation(Component *t_component);
   };

   class ComponentTypeParameterAsOutput:public ComponentType {
   public:
      ComponentTypeParameterAsOutput();
      void Execute(Component *t_component);
   };

}

#endif
