#include "../../include/evolution.h"

using namespace evolution;


Individual::Individual(ComponentManager *t_component_manager,ComponentLibrary *t_component_library) {
   m_evolutionary_program.SetComponentManager(t_component_manager);
   m_evolutionary_program.SetComponentLibrary(t_component_library);
   //m_program = new EvolutionaryProgram(t_component_manager);

   m_component_manager = t_component_manager;
   m_component_library = t_component_library;
   m_dirty = false;
   m_age = 0;
}

Individual::~Individual() {
}


double Individual::GetAverageFitness(void) {
   return m_fitness.GetAverageFitness();
}

void Individual::SetObjectiveFitness(int t_objective,double t_fitness) {
   m_fitness.SetObjectiveFitness(t_objective, t_fitness);
}

EvolutionaryProgram *Individual::GetEvolutionaryProgram(void) {
   return &m_evolutionary_program;
}

bool Individual::MutateParameters(double t_mutation_chance) {
   double r = ((double) rand() / (RAND_MAX));
   if (r < t_mutation_chance) {
      m_evolutionary_program.MutateParameters();
      m_dirty = true;
      return true;
   }
   return false;
}

bool Individual::MutateStructure(double t_mutation_chance) {
   double r = ((double) rand() / (RAND_MAX));
   if (r < t_mutation_chance) {
      m_evolutionary_program.MutateStructure();
      m_dirty = true;
      return true;
   }
   return false;
}

void Individual::Crossover(Individual *t_parent1, Individual *t_parent2) {
   m_evolutionary_program.Crossover(t_parent1->GetEvolutionaryProgram(), t_parent2->GetEvolutionaryProgram());
   m_dirty = true;
}

void Individual::Execute(void) {
   m_evolutionary_program.Execute();
}

void Individual::Randomize(void) {
   m_evolutionary_program.Randomize();
   m_dirty = true;
}

void Individual::CopyFrom(Individual *t_individual) {
   m_fitness.CopyFrom(&t_individual->m_fitness);
   m_evolutionary_program.SetComponentManager(m_component_manager);
   m_evolutionary_program.SetComponentLibrary(m_component_library);
   m_evolutionary_program.CopyFrom(&t_individual->m_evolutionary_program);
}

bool Individual::Dirty(void){
   return m_dirty;
}

void Individual::ClearDirty(void){
   m_dirty = false;
}

void Individual::Die(void) {
   m_evolutionary_program.Cleanup();
}

double Individual::GetAge(void) {
   return m_age;
}

void Individual::SetAge(double t_age) {
   m_age = t_age;
}
