//
// Created by Nuno on 29/12/2021.
//

#ifndef PROJETO_LP_AED_GENETICALGORITHM_H
#define PROJETO_LP_AED_GENETICALGORITHM_H

#include "creation_resizing.h"
#include "csvData.h"
#include "tripsandcities.h"

typedef struct individuals {
    double *fitness;
    double finess_sum;
    int **individual;
    int **nextindividual;
} INDIVIDUAL;

typedef struct population {
    int generation;
    int **bestIndividuals;
    struct population *next;
    INDIVIDUAL individuals;
} POPULATION;

/**
 * Cria uma população aleatória a partir de um array que é baralhado
 * Tem complexidade temporal de O(n log n)
 * @param population
 * @param populationSize
 * @return population
 */
POPULATION *initialPop(POPULATION *population, int populationSize);

/**
 *
 * @param cities
 * @param population
 * @param populationSize
 * @param elitismNumber
 * @param mutationRate
 * @param generations
 * @param ID
 * @return population
 */
POPULATION *
cycleGeneration(CITYNODE *cities, POPULATION *population, int populationSize, int elitismNumber, double mutationRate,
                int generations, int ID);

/**
 * Função para calcular a fitness de cada indivíduo.
 * @param cities
 * @param population
 * @param populationSize
 * @return population
 */
POPULATION *evaluate_fitness(CITYNODE *cities, POPULATION *population, int populationSize);

/**
 * Calcula a distância entre cidades.
 * @param cities
 * @param id_1
 * @param id_2
 * @return dist
 */
double calculateDistance(CITYNODE *cities, int id_1, int id_2);
/**
 * Escolhe n indivíduos por elitismo ( maior valor de fitness ).
 * @param population
 * @param elitismNumber
 * @param populationSize
 * @return population
 */
POPULATION *elitism(POPULATION *population, int elitismNumber, int populationSize);

/**
 *
 * @param population
 * @param elitismNumber
 * @param populationSize
 * @param fitness_sum
 * @return population
 */
POPULATION *selection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum);
/**
 * Indivíduos com maior fitness, têm maior probabilidade de serem escolhidos, logo foi gerado um numero entre 0 e a soma de todas as fitness, fazendo Roulette Wheel.
 * @param population
 * @param elitismNumber
 * @param populationSize
 * @param fitness_sum
 * @return population
 */
POPULATION *probSelection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum);
/**
 * Cruzamento de indivíduos selecionados previamente por elitismo e Roulette Wheel.
 * Foi implementado o algoritmo PMX crossover que tem complexidade temporal  O(n!).
 * @param population
 * @param populationSize
 * @param elitismNumber
 * @param mutationRate
 * @return population
 */
POPULATION *crossover(POPULATION *population, int populationSize, int elitismNumber, double mutationRate);
/**
 * remove duplicados em cada array de indivíduos.
 * @param population
 * @param i
 * @param populationSize
 * @return u
 */
int replaceDuplicate(POPULATION *population, int i, int popuLationSize);
/**
 * É inserido um valor de mutação entre 0 e 1 para gerar a probabilidade de haver mutação nos indivíduos.
 * @param population
 * @param mutationRate
 * @param populationSize
 * @return population
 */
POPULATION *mutation(POPULATION *population, double mutationRate, int populationSize);
/**
 * Procura geração por ID de geração e imprime a população.
 * @param population
 * @param ID
 * @param populationSize
 */
void searchGenerationID(POPULATION *population, int ID, int populationSize);
/**
 *
 * @param cities
 * @param population
 * @param populationSize
 * @param elitismNumber
 * @param mutationRate
 * @param generation
 * @return
 */
POPULATION *createNode(CITYNODE *cities, POPULATION *population, int populationSize, int elitismNumber, double mutationRate, int generation);

#endif //PROJETO_LP_AED_GENETICALGORITHM_H
