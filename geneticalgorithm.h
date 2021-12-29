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
    int distance;
    struct nodeInfo *next;
} NODEINFO;

typedef struct population {
    int **path;
} POPULATION;

#endif //PROJETO_LP_AED_GENETICALGORITHM_H
