//
// Created by Nuno on 29/12/2021.
//

#include "geneticalgorithm.h"


POPULATION *createPopulation(CITYNODE *cities, POPULATION *population, int populationSize) {
    int i = 1, j = 1;
    int generation = 0;
    double fitness_sum;
    POPULATION *pophead, *prevPop, *newPop;
    srand(time(NULL));
    // First iteration
    prevPop = initialPop(population, populationSize);
    pophead = prevPop;

    // 2-Populationsizeth
    while (i != populationSize) {
        newPop = initialPop(population, populationSize);
        prevPop->next = newPop;
        prevPop = newPop;
        prevPop->next = NULL;
        i++;
    }

    fitness_sum = evaluate_fitness(cities, pophead);

    generation++;
    POPULATION *currentNode = pophead;
    while(currentNode != NULL){
        currentNode->individuals.probability = currentNode->individuals.fitness / fitness_sum;
        currentNode->generation = generation;
        currentNode= currentNode->next;
    }

    printf("Random population generation completed");
    return pophead;
}

double evaluate_fitness(CITYNODE *cities, POPULATION *population) {
    int id_1, id_2;
    double fitness_sum = 0;
    double total = 0;
    while (population != NULL) {
        for (int j = 0; j < 10; ++j) {
            id_1 = population->individuals.individual[j];
            id_2 = population->individuals.individual[j + 1];
            total += calculateDistance(cities, id_1, id_2);
        }
        population->individuals.fitness = 1 / total;
        fitness_sum += population->individuals.fitness;
        total = 0;
        population = population->next;
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
    population->individuals.individual = malloc(sizeof(int) * populationSize);
    int x, temp, i;
    for (int u = 0; u < populationSize; u++) {
        //Fill array with desired numbers
        for (temp = 0, i = 1; temp < 10; i++, temp++) {
            population->individuals.individual[temp] = i;
        }
        for (int j = 9; j > 0; j--) {
            x = rand() % j;     // rand number
            //shuffling
            temp = population->individuals.individual[j];
            population->individuals.individual[j] = population->individuals.individual[x];
            population->individuals.individual[x] = temp;
        }
    }

    return population;
}


