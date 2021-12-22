//
// Created by Nuno on 20/12/2021.
//

#ifndef PROJETO_LP_AED_CREATION_RESIZING_H
#define PROJETO_LP_AED_CREATION_RESIZING_H

#include <stdio.h>
#include <stdlib.h>
#include "libs_src/lib_stats.h"
#include "libs_src/lib_util.h"
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define BUFFER_SIZE 1024


typedef struct customer {
    int ID;
    int number;
    struct birth {
        int day, month, year;
    } birthday;
    struct REGISTER {
        int day, month, year;
    } registerdate;
    char* address;
    int billingcost;
} CUSTOMER;

typedef struct node {
    CUSTOMER customer;
    struct node *next;
} LIST_QUEUE_NODE;


LIST_QUEUE_NODE * StoreCustomers();
LIST_QUEUE_NODE *addCustomerHead(LIST_QUEUE_NODE *head, struct customer a);
void printList(LIST_QUEUE_NODE *head);
LIST_QUEUE_NODE * csvToNode(char *token, char* row);
LIST_QUEUE_NODE * nodeToCSV(LIST_QUEUE_NODE *head);

#endif //PROJETO_LP_AED_CREATION_RESIZING_H
