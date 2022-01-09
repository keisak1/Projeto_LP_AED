//
// Created by Nuno on 29/12/2021.
//

#include "geneticalgorithm.h"


POPULATION *
cycleGeneration(CITYNODE *cities, POPULATION *population, int populationSize, int elitismNumber, double mutationRate,
                int generations, int ID) {

    int generation = 1;
    POPULATION *pophead;
    POPULATION *newPop;
    POPULATION *prevPop;
    srand(time(NULL));

    prevPop = initialPop(population, populationSize);
    printf("Random population generation completed\n");
    prevPop = createNode(cities, prevPop, populationSize, elitismNumber, mutationRate, generation);
    pophead = prevPop;
    for (int i = 0; i < generations - 1; ++i) {
        newPop = createNode(cities, prevPop, populationSize, elitismNumber, mutationRate, i+2);
        prevPop->next->next = newPop;
        prevPop = newPop;
        prevPop->next->next = NULL;
    }

    searchGenerationID(pophead, ID, populationSize);
    return pophead;
}

POPULATION *evaluate_fitness(CITYNODE *cities, POPULATION *population, int populationSize) {
    /**
     * @param cities, population, populationSize
     *
     * Função para calcular a fitness de cada indivíduo.
     * @return population
     */
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
        printf("Individual[%d]: %f\n", i + 1, population->individuals.fitness[i]);
    }

    return population;

}


double calculateDistance(CITYNODE *cities, int id_1, int id_2) {
    /**
     * Calcular a distância entre cidades.
     */
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
    /**
     * Cria uma população aleatória a partir de um array que é baralhado
     * Tem complexidade temporal de O(n log n)
     */
    population = (struct population *) malloc(sizeof(POPULATION));

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


POPULATION *selection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum) {
    population = elitism(population, elitismNumber, populationSize);
    population = probSelection(population, elitismNumber, populationSize, fitness_sum);

    return population;
}

POPULATION *elitism(POPULATION *population, int elitismNumber, int populationSize) {
    // return index of n = elitismNumber, numbers of fitness array
    /**
     *  Escolhe n indivíduos por elitismo ( maior valor de fitness ).
     */

    double *temp, a;
    population->individuals.nextindividual = (int **) malloc(sizeof(int *) * populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population->individuals.nextindividual[i] = (int *) malloc(sizeof(int) * populationSize);
    }
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

    population->bestIndividuals = (int **) malloc(sizeof(int *) * populationSize);
    for (int i = 0; i < 2; ++i) {
        population->bestIndividuals[i] = (int *) malloc(sizeof(int) * populationSize);
    }
    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < elitismNumber; ++j) {
            if (population->individuals.fitness[i] == temp[j]) {
                for (int l = 0; l < populationSize; ++l) {
                    population->individuals.nextindividual[k][l] = population->individuals.individual[i][l];
                }
                for (int u = 0; u < 2; ++u) {
                    for (int m = 0; m < populationSize; ++m) {
                        population->bestIndividuals[u][m] = population->individuals.nextindividual[k][m];
                    }
                }
                k++;
                if (k == elitismNumber) {
                    return population;
                }
            }
        }
    }
    free(temp);
}

POPULATION *probSelection(POPULATION *population, int elitismNumber, int populationSize, double fitness_sum) {
    /**
     * Indivíduos com maior fitness, têm maior probabilidade de serem escolhidos, logo foi gerado um numero entre 0 e a soma de todas as fitness, fazendo Roulette Wheel.
     */
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

    return population;
}

POPULATION *crossover(POPULATION *population, int populationSize, int elitismNumber, double mutationRate) {
    /**
     *  Cruzamento de indivíduos selecionados previamente por elitismo e Roulette Wheel.
     *  Foi implementado o algoritmo PMX crossover que tem complexidade temporal  O(n!).
     */
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

        for (int j = crossPoint2 + 1; j < populationSize; ++j) {
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

    int num;

    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < populationSize; ++j) {
            if (j < crossPoint1 || j > crossPoint2) {
                num = population->next->individuals.individual[i][j];
                for (int k = j + 1; k < populationSize; ++k) {
                    if (num == population->next->individuals.individual[i][k]) {
                        population->next->individuals.individual[i][j] = replaceDuplicate(population, i,
                                                                                          populationSize);
                    }
                }
            }
        }
    }

    population = mutation(population, mutationRate, populationSize);


    return population;
}


int replaceDuplicate(POPULATION *population, int i, int populationSize) {
    /**
     * remove duplicados em cada array de indivíduos.
     */
    int u, notduplicate;
    for (u = 1; u < 10; ++u) {
        notduplicate = 0;
        for (int k = 0; k < populationSize; ++k) {
            if (u != population->next->individuals.individual[i][k]) {
                notduplicate += 1;
                if (notduplicate == 10) {
                    return u;
                }
            }
        }
    }
}

POPULATION *mutation(POPULATION *population, double mutationRate, int populationSize) {
    /**
     * É inserido um valor de mutação entre 0 e 1 para gerar a probabilidade de haver mutação nos indivíduos.
     */
    int p = RAND_MAX * mutationRate;
    for (int i = 0; i < populationSize; ++i) {
        if (rand() < p) {
            int randCity1 = rand() % populationSize;
            int randCity2 = rand() % populationSize;
            int temp = population->next->individuals.individual[i][randCity1];
            population->next->individuals.individual[i][randCity1] = population->next->individuals.individual[i][randCity2];
            population->next->individuals.individual[i][randCity2] = temp;
        }
    }

    printf("\nGeneration %d\n", population->generation);
    for (int j = 0; j < populationSize; j++) {
        for (int x = 0; x < populationSize; x++) {
            printf("%d\t", population->next->individuals.individual[j][x]);
        }
        printf("\n");
    }
    return population;
}

void searchGenerationID(POPULATION *population, int ID, int populationSize) {
    /**
     * Procura geração por ID de geração e imprime a população.
     */
    while (population != NULL) {
        if (population->generation == ID) {
            printf("Finding ID...\n");
            printf("Generation ID: %d\n", population->generation);
            for (int i = 0; i < populationSize; ++i) {
                printf("Fitness: %f\n", population->individuals.fitness[i]);
            }
            printf("Individuals:\n");
            for (int i = 0; i < populationSize; i++) {
                for (int j = 0; j < populationSize; j++) {
                    printf("%d\t", population->individuals.individual[i][j]);
                }
                printf("\n");
            }
        }
        population = population->next;
    }
}

POPULATION *createNode(CITYNODE *cities, POPULATION *population, int populationSize, int elitismNumber, double mutationRate, int generation) {
    /**
     * Auxílio na criação de um node.
     */
    population->generation= generation;
    population = evaluate_fitness(cities, population, populationSize);
    population = selection(population, elitismNumber, populationSize, population->individuals.finess_sum);
    population = crossover(population, populationSize, elitismNumber, mutationRate);
    population = population->next;


    return population;
}