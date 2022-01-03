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
    double *probability;
    int **individual;
    int **nextindividual;
} INDIVIDUAL;

typedef struct population {
    int generation;
    int bestIndividuals;
    struct population *next;
    INDIVIDUAL individuals;
} POPULATION;


POPULATION *initialPop(POPULATION *population, int populationSize);
POPULATION *createPopulation(CITYNODE *cities, POPULATION *population, int populationSize, int elitismNumber);
double evaluate_fitness(CITYNODE *cities, POPULATION *population);
double calculateDistance(CITYNODE *cities, int id_1, int id_2);
POPULATION *elitism(POPULATION *population, int elitismNumber, int populationSize);
POPULATION *selection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum);
POPULATION *probSelection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum);


#endif //PROJETO_LP_AED_GENETICALGORITHM_H
