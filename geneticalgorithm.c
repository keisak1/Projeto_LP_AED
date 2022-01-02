//
// Created by Nuno on 29/12/2021.
//

#include "geneticalgorithm.h"


POPULATION *createPopulation(CITYNODE *cities, POPULATION *population, int populationSize) {

    int generation = 0;
    double fitness_sum;
    POPULATION *pophead, *prevPop, *newPop;
    srand(time(NULL));
    pophead = initialPop(population, populationSize);


    fitness_sum = evaluate_fitness(cities, pophead);

    generation++;
    for (int j = 0; j < populationSize; ++j) {
        pophead->individuals.probability[j] = pophead->individuals.fitness[j] / fitness_sum;
        pophead->generation = generation;
    }



    printf("Random population generation completed");
    return pophead;
}

double evaluate_fitness(CITYNODE *cities, POPULATION *population) {
    for (int i = 0; i < 10; ++i) {
        population->individuals.fitness = (double *) malloc(sizeof(double) * 10);
        population->individuals.probability = (double *) malloc(sizeof(double) * 10);

    }
    int id_1, id_2;
    double fitness_sum = 0;
    double total = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            id_1 = population->individuals.individual[i][j];
            id_2 = population->individuals.individual[i][j + 1];
            total += calculateDistance(cities, id_1, id_2);
        }
        population->individuals.fitness[i] = 1 / total;
        total = 0;
        fitness_sum += population->individuals.fitness[i];
    }

    return fitness_sum;

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

POPULATION *initialPop(POPULATION *population, int populationSize) {
    population = (struct population *) malloc(sizeof(POPULATION) * populationSize);

    population->individuals.individual = (int **) malloc(sizeof(int *) * populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population->individuals.individual[i] = (int *) malloc(sizeof(int) * populationSize);
    }
    int x, temp, i;
    for (int u = 0; u < populationSize; u++) {
        //Fill array with desired numbers
        for (temp = 0, i = 1; temp < 10; i++, temp++) {
            population->individuals.individual[u][temp] = i;
        }
        for (int j = 9; j > 0; j--) {
            x = rand() % j;     // rand number
            //shuffling
            temp = population->individuals.individual[u][j];
            population->individuals.individual[u][j] = population->individuals.individual[u][x];
            population->individuals.individual[u][x] = temp;
        }
    }

    return population;
}

/*
POPULATION *highest_fitness(POPULATION *population) {
    POPULATION *currentNode = population;
    double initial = currentNode->individuals.fitness;
    while (currentNode != NULL) {
        if (currentNode->individuals.fitness > initial) {
            initial = currentNode->individuals.fitness;
        }
        currentNode = currentNode->next;
    }

}*/