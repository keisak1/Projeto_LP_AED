//
// Created by Nuno on 29/12/2021.
//

#include "geneticalgorithm.h"


void createPopulation(POPULATION *population, int populationSize) {
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
    printf("Random population generation completed");
}

double *evaluate_fitness(CITYNODE *cities, POPULATION *population, int populationSize) {
    int id_1, id_2;
    double total;
    for (int i = 0; i < populationSize; ++i) {
        total = 0;
        for (int j = 0; j < 10; ++j) {
            id_1 = population[i].path[j];
            total += calculateDistance(cities, id_1);
        }
        population[i].fitness = 1 / total;
    }
}


double calculateDistance(CITYNODE *cities, int id_1) {
    double dist;
    while (cities != NULL) {
        if (cities->city.ID == id_1) {
            double x1 = cities->city.x;
            double y1 = cities->city.y;
            double x2 = cities->nextcity->city.x;
            double y2 = cities->nextcity->city.y;
            dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        }
        cities = cities->nextcity;
    }
    return dist;
}
