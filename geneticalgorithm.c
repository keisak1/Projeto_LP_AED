//
// Created by Nuno on 29/12/2021.
//

#include "geneticalgorithm.h"


void createPopulation(CITYNODE *cities, POPULATION *population, int populationSize) {
    population = malloc(sizeof(POPULATION) * populationSize);
    int x, temp, i;
    int num[10];
    srand(time(NULL));
    //Fill array with desired numbers
    for (temp = 0, i = 1; temp < 10; i++, temp++) {
        num[temp] = i;
    }
    for (int u = 0; u < populationSize; u++) {
        for (int j = 9; j > 0; j--) {
            x = rand() % j;     // rand number
            //swapping
            temp = num[j];
            num[j] = num[x];
            num[x] = temp;
            for (int k = 0; k < 10; ++k) {
                population[u].path[k] = num[k];
            }
        }
    }
    evaluate_fitness(cities, population, populationSize);
    printf("Random population generation completed");
}

double *evaluate_fitness(CITYNODE *cities, POPULATION *population, int populationSize) {
    int id_1, id_2;
    double total;
    for (int i = 0; i < populationSize; ++i) {
        total = 0;
        for (int j = 0; j < 10; ++j) {
            id_1 = population[i].path[j];
            id_2 = population[i].path[j + 1];
            total += calculateDistance(cities, id_1, id_2);
        }
        population[i].fitness = 1 / total;
        printf("\nFitness: %f\n", population[i].fitness); // NAO ESQUECER DE APAGAR
    }
}


double calculateDistance(CITYNODE *cities, int id_1, int id_2) {
    double dist, x1, x2, y1, y2;
    while (cities != NULL) {
        if (cities->city.ID == id_1) {
            x1 = cities->city.x;
            y1 = cities->city.y;
        }
        if (cities->city.ID == id_2) {
            x2 = cities->city.x;
            y2 = cities->city.y;
        }
        cities = cities->nextcity;
    }
    dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return dist;
}