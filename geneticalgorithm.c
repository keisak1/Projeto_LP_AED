//
// Created by Nuno on 29/12/2021.
//

#include "geneticalgorithm.h"


POPULATION *createPopulation(CITYNODE *cities, POPULATION *population, int populationSize, int elitismNumber) {
    int generation = 0;
    double fitness_sum;
    POPULATION *pophead;

    srand(time(NULL));
    pophead = initialPop(population, populationSize);


    fitness_sum = evaluate_fitness(cities, pophead);

    generation++;
    for (int j = 0; j < populationSize; ++j) {
        pophead->individuals.probability[j] = pophead->individuals.fitness[j] / fitness_sum;
        pophead->generation = generation;
    }
    pophead = selection(pophead, elitismNumber, populationSize, fitness_sum);

    printf("Random population generation completed\n");
    return pophead;
}

double evaluate_fitness(CITYNODE *cities, POPULATION *population) {
    population->individuals.fitness = (double *) malloc(sizeof(double) * 10);
    population->individuals.probability = (double *) malloc(sizeof(double) * 10);

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
    population->individuals.nextindividual = (int **) malloc(sizeof(int *) * populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population->individuals.nextindividual[i] = (int *) malloc(sizeof(int) * populationSize);
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


POPULATION *selection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum) {
    population = elitism(population, elitismNumber, populationSize);
    population = probSelection(population, elitismNumber, populationSize, fitness_sum);

    return population;
}

POPULATION *elitism(POPULATION *population, int elitismNumber, int populationSize) {
    // return index of n = elitismNumber, numbers of fitness array

    double *temp, a;
    temp = (double *) malloc(sizeof(double) * populationSize);
    int k = 0;
    for (int i = 0; i < populationSize; ++i) {
        temp[i] = population->individuals.fitness[i];
    }
    for (int i = 0; i < populationSize; ++i) {
        for (int j = i + 1; j < populationSize; ++j) {
            if (temp[i] < temp[j]) {
                a = temp[i];
                temp[i] = temp[j];
                temp[j] = a;
            }
        }
    }
    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < elitismNumber; ++j) {
            if (population->individuals.fitness[i] == temp[j]) {
                for (int l = 0; l < populationSize; ++l) {
                    population->individuals.nextindividual[k][l] = population->individuals.individual[i][l];
                }
                k++;
            }
        }
    }
    for (int i = 0; i < populationSize; i++) {
        for (int j = 0; j < populationSize; j++) {
            printf("%d\t", population->individuals.nextindividual[i][j]);
        }
        printf("\n");
    }
    return population;
}

POPULATION *probSelection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum) {
    double extraction;
    int pivot, first, last, k = 0;
    int *candidates = malloc(sizeof(int) * (populationSize - elitismNumber));

    for (int i = 0; i < populationSize - elitismNumber; i++) {

        first = 0;
        last = populationSize;
        extraction = (double) rand() /fitness_sum;   //rand() generates a number in [0, RAND_MAX] therefore dividing by RAND_MAX we obtain a value in [0, 1]

        while (first !=last) {  //Binary search of the first element of the CDF that has bigger probability than the value randomly generated
            pivot = (first + last) / 2;
            if (population->individuals.probability[pivot] == extraction) {
                break;
            }
            if (population->individuals.probability[pivot] > extraction) {
                last = pivot;
            } else {
                first = pivot + 1;
            }
        }
        candidates[i] = first; //candidates[i] contains the index of the extracted individual, the bigger the probability, the more the index appears in candidates (so it reproduces often because it's a good solution)
    }

    for (int i = elitismNumber ; i < populationSize; ++i) {
        for (int l = 0; l < populationSize; ++l) {
            population->individuals.nextindividual[i][l] = population->individuals.individual[candidates[k]][l];
        }
        k++;
    }
    for (int i = 0; i < populationSize; i++) {
        for (int j = 0; j < populationSize; j++) {
            printf("%d\t", population->individuals.nextindividual[i][j]);
        }
        printf("\n");
    }
    return population;
}