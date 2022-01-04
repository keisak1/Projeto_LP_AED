//
// Created by Nuno on 29/12/2021.
//

#include "geneticalgorithm.h"


POPULATION *
cycleGeneration(CITYNODE *cities, POPULATION *population, int populationSize, int elitismNumber, double mutationRate, int generations) {
    int generation = 0;

    POPULATION *pophead;

    srand(time(NULL));

    pophead = initialPop(population, populationSize);

    printf("Random population generation completed\n");


    for (int i = 0; i < generations; ++i) {

        pophead = evaluate_fitness(cities, pophead, populationSize);

        generation++;

        pophead->generation = generation;

        pophead = selection(pophead, elitismNumber, populationSize, pophead->individuals.finess_sum);
        pophead = crossover(pophead, populationSize, elitismNumber, mutationRate);

        printf("\nGeneration %d\n", generation);
        for (int j = 0; j < populationSize; j++) {
            for (int x = 0; x < populationSize; x++) {
                printf("%d\t", population->individuals.individual[j][x]);
            }
            printf("\n");
        }
    }
    return pophead;
}

POPULATION *evaluate_fitness(CITYNODE *cities, POPULATION *population, int populationSize) {
    population->individuals.fitness = (double *) malloc(sizeof(double) * populationSize);

    int id_1, id_2;
    double total = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            id_1 = population->individuals.individual[i][j];
            id_2 = population->individuals.individual[i][j + 1];
            total += calculateDistance(cities, id_1, id_2);
        }
        population->individuals.fitness[i] = 1 / total;
        total = 0;
        population->individuals.finess_sum += population->individuals.fitness[i];
    }
    for (int i = 0; i < populationSize; ++i) {
        printf("%f\n", population->individuals.fitness[i]);
    }

    return population;

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
    population = (struct population *) malloc(sizeof(POPULATION));

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
    return population;
}

POPULATION *probSelection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum) {
    double random;
    int k = 0, j;
    int *candidates = malloc(sizeof(int) * (populationSize - elitismNumber));

    for (int i = 0; i < populationSize - elitismNumber; i++) {
        random = ((double) rand()) /
                 RAND_MAX;   //rand() generates a number in [0, RAND_MAX] therefore dividing by RAND_MAX we obtain a value in [0, 1]
        random = random * fitness_sum; // [0, fitness_sum]

        for (j = 0; j < populationSize && random > 0; j++) {
            random -= population->individuals.fitness[j];
        }
        candidates[i] = j -
                        1;//candidates[i] contains the index of the extracted individual, the bigger the probability, the more the index appears in candidates

    }

    for (int i = elitismNumber; i < populationSize; ++i) {
        for (int l = 0; l < populationSize; ++l) {
            population->individuals.nextindividual[i][l] = population->individuals.individual[candidates[k]][l];
        }
        k++;
    }

    for (int i = 0; i < populationSize; i++) {
        for (int x = 0; x < populationSize; x++) {
            printf("%d\t", population->individuals.nextindividual[i][x]);
        }
        printf("\n");
    }
    return population;
}

POPULATION *crossover(POPULATION *population, int populationSize, int elitismNumber, double mutationRate) {

    // allocating memory

    population->next = (struct population *) malloc(sizeof(POPULATION));
    population->next->individuals.individual = (int **) malloc(sizeof(int *) * populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population->next->individuals.individual[i] = (int *) malloc(sizeof(int) * populationSize);
    }
    population->next->individuals.nextindividual = (int **) malloc(sizeof(int *) * populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population->next->individuals.nextindividual[i] = (int *) malloc(sizeof(int) * populationSize);
    }

    //................................................

    // PMX crossover algorithm

    int crossPoint1 = (populationSize / 2) - 1;
    int crossPoint2 = populationSize - ((populationSize / 2) - 1);
    for (int i = elitismNumber; i < populationSize; i = i + 2) {
        for (int j = crossPoint1; j <= crossPoint2; ++j) {
            population->next->individuals.individual[i][j] = population->individuals.nextindividual[i + 1][j];
            population->next->individuals.individual[i + 1][j] = population->individuals.nextindividual[i][j];
        }
    }

    for (int i = elitismNumber; i < populationSize; i = i + 2) {
        for (int j = 0; j < crossPoint1; ++j) {
            population->next->individuals.individual[i][j] = population->individuals.nextindividual[i + 1][j];
            population->next->individuals.individual[i + 1][j] = population->individuals.nextindividual[i][j];
        }

        for (int j = crossPoint2; j < populationSize; ++j) {
            population->next->individuals.individual[i + 1][j] = population->individuals.nextindividual[i][j];
            population->next->individuals.individual[i][j] = population->individuals.nextindividual[i + 1][j];
        }
    }


    // elitism

    for (int i = 0; i < elitismNumber; ++i) {
        for (int j = 0; j < populationSize; ++j) {
            population->next->individuals.individual[i][j] = population->individuals.nextindividual[i][j];
        }
    }

    population = population->next;
    int num;

    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < populationSize; ++j) {
            if (j < crossPoint1 || j > crossPoint2) {
                num = population->individuals.individual[i][j];
                for (int k = j + 1; k < populationSize; ++k) {
                    if (num == population->individuals.individual[i][k]) {
                        population->individuals.individual[i][j] = replaceDuplicate(population, i, populationSize);
                    }
                }
            }
        }
    }

    population = mutation(population, mutationRate, populationSize);


    return population;
}


int replaceDuplicate(POPULATION *population, int i, int populationSize) {
    int u, notduplicate;
    for (u = 1; u < 10; ++u) {
        notduplicate = 0;
        for (int k = 0; k < populationSize; ++k) {
            if (u != population->individuals.individual[i][k]) {
                notduplicate += 1;
                if (notduplicate == 10) {
                    return u;
                }
            }
        }
    }
}

POPULATION *mutation(POPULATION *population, double mutationRate, int populationSize) {
    int p = RAND_MAX * mutationRate;

    for (int i = 0; i < populationSize; ++i) {
        if (rand() < p) {
            int randCity1 = rand() % 10 + 1;
            int randCity2 = rand() % 10 + 1;
            int temp = population->individuals.individual[i][randCity1];
            population->individuals.individual[i][randCity1] = population->individuals.individual[i][randCity2];
            population->individuals.individual[i][randCity2] = temp;
        }
    }

    return population;
}

