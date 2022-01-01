//
// Created by Nuno on 29/12/2021.
//

#ifndef PROJETO_LP_AED_GENETICALGORITHM_H
#define PROJETO_LP_AED_GENETICALGORITHM_H

#include "creation_resizing.h"
#include "csvData.h"
#include "tripsandcities.h"

typedef struct nodeInfo {
    int individuals;
    double distance;
    struct nodeInfo *next;
} NODEINFO;

typedef struct population {
    int path[10];
    double fitness;
} POPULATION;

typedef struct pathdistance {
    double matrix[10][10];
} PATHDISTANCE;

/*
PATHDISTANCE test3 = (PATHDISTANCE){.matrix= {
        {0, 2.23, 3.0,  1.41, 2.19, 4.0,  5.0,  5.0,  5.0,  5.83}, // 1 cidade
        {0, 2.23, 1.41, 2.23, 4.42, 3.60, 3.16, 5.83, 6.32, 7.28}, // 2 cidade
        {0, 3.0,  1.41, 2.23, 5.08, 5.0,  4.0,  7.21, 7.61, 8.54}, // 3 cidade
        {0, 1.41, 2.23, 2.23, 3.0,  5.09, 5.38, 6.40, 6.40, 7.21}, // 4 cidade
        {0, 2.19, 4.42, 5.08, 3.0,  5.29, 7.0,  5.0,  4.38, 4.92}, // 5 cidade
        {0, 4.0,  3.60, 5.0,  5.09, 5.29, 3.0,  3.0,  4.12, 5.09}, // 6 cidade
        {0, 5.0,  3.16, 4.0,  5.38, 7.0,  3.0,  6.0,  7.07, 8.06}, // 7 cidade
        {0, 5.0,  5.83, 7.21, 6.40, 5.0,  3.0,  6.0,  1.41, 2.23}, // 8 cidade
        {0, 5.0,  6.32, 7.61, 6.40, 4.38, 4.12, 7.07, 1.41, 1.0}, // 9 cidade
        {0, 5.83, 7.28, 8.54, 7.21, 4.92, 5.09, 8.06, 2.23, 1.0} // 10 cidade
}};*/

void createPopulation(POPULATION *population, int populationSize);
double * evaluate_fitness(CITYNODE * cities, POPULATION * population, int populationSize);
double calculateDistance(CITYNODE * cities, int id_1);

#endif //PROJETO_LP_AED_GENETICALGORITHM_H
