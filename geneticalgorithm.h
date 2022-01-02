//
// Created by Nuno on 29/12/2021.
//

#ifndef PROJETO_LP_AED_GENETICALGORITHM_H
#define PROJETO_LP_AED_GENETICALGORITHM_H

#include "creation_resizing.h"
#include "csvData.h"
#include "tripsandcities.h"

typedef struct nodeInfo {
    int individual;
    double fitness;
    struct nodeInfo *next;
} NODEINFO;

typedef struct population {
    int path[10];
    double fitness;
} POPULATION;


void createPopulation(CITYNODE *cities, POPULATION *population, int populationSize);
double * evaluate_fitness(CITYNODE * cities, POPULATION * population, int populationSize);
double calculateDistance(CITYNODE * cities, int id_1, int id_2);

#endif //PROJETO_LP_AED_GENETICALGORITHM_H
