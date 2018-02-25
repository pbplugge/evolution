#include "../../include/evolution.h"

using namespace evolution;


Config::Config() {
   m_maximum_number_of_generations = 100;
   m_minimum_population_size = 10;
   m_maximum_population_size = 300;
   m_structure_mutation_chance = 0.1f;
   m_parameter_mutation_chance = 0.1f;
   m_crossover_chance = 0.1f;
   m_random_individual_chance = 0.01f;
   m_randomize_after_generations_without_improvement = 3000000;
}

void Config::SetMaximumGenerations(int t_maximum_number_of_generations) {
   m_maximum_number_of_generations = t_maximum_number_of_generations;
}

int Config::GetMaximumGenerations(void) {
   return m_maximum_number_of_generations;
}

void Config::SetMinimumPopulationSize(int t_minimum_population_size) {
   m_minimum_population_size = t_minimum_population_size;
}

int Config::GetMinimumPopulationSize(void) {
   return m_minimum_population_size;
}

void Config::SetMaximumPopulationSize(int f_maximum_population_size) {
   m_maximum_population_size = f_maximum_population_size;
}

int Config::GetMaximumPopulationSize(void){
   return m_maximum_population_size;
}

double Config::GetStructureMutationChance(void){
   return m_structure_mutation_chance;
}

void Config::SetStructureMutationChance(double f_structure_mutation_chance){
   m_structure_mutation_chance = f_structure_mutation_chance;
}

double Config::GetParameterMutationChance(void) {
   return m_parameter_mutation_chance;
}

void Config::SetParameterMutationChance(double f_parameter_mutation_chance) {
   m_parameter_mutation_chance = f_parameter_mutation_chance;
}

void Config::SetCrossoverChance(double t_crossover_chance) {
   m_crossover_chance = t_crossover_chance;
}

double Config::GetCrossoverChance(void) {
   return m_crossover_chance;
}

void Config::SetRandomIndividualChance(double t_random_individual_chance) {
   m_random_individual_chance = t_random_individual_chance;
}

double Config::GetRandomIndividualChance(void) {
   return m_random_individual_chance;
}

int Config::GetRandomizeAfterGenerationsWithoutImprovement(void){
   return m_randomize_after_generations_without_improvement;
}

void Config::SetRandomizeAfterGenerationsWithoutImprovement(int t_generations) {
   m_randomize_after_generations_without_improvement = t_generations;
}

