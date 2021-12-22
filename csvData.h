//
// Created by Nuno on 22/12/2021.
//

#ifndef PROJETO_LP_AED_CSVDATA_H
#define PROJETO_LP_AED_CSVDATA_H
#include "creation_resizing.h"

LIST_QUEUE_NODE * csvToNode(char *token, char* row);
LIST_QUEUE_NODE * nodeToCSV(LIST_QUEUE_NODE *head);
LIST_QUEUE_NODE * appendnodeToCSV(LIST_QUEUE_NODE *tail);
void insertCustomerData(LIST_QUEUE_NODE *newNode);
#endif //PROJETO_LP_AED_CSVDATA_H
