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

typedef  struct city{
    int ID;
    char *name;
    struct poi {
        int beaches, museums, parks;
    } PoI;
}CITY;

typedef struct cityNode {
    CITY city;
    struct city *nextcity;
} CITYNODE;

typedef struct trips {
   int *citiesvisited;
} TRIPS;


typedef struct customer {
    int NIF;
    int number;
    struct birth {
        int day, month, year;
    } birthday;
    struct REGISTER {
        int day, month, year;
    } registerdate;
    char *address;
    int billingcost;
    TRIPS trips;
} CUSTOMER;

typedef struct node {
    CUSTOMER customer;
    struct node *next;
} LIST_QUEUE_NODE;


LIST_QUEUE_NODE *StoreCustomers();

LIST_QUEUE_NODE *addCustomerHead(LIST_QUEUE_NODE *head);

void addCustomerTail(LIST_QUEUE_NODE *tail);

void printList(LIST_QUEUE_NODE *head);

LIST_QUEUE_NODE *deleteCustomer(LIST_QUEUE_NODE *head);

LIST_QUEUE_NODE *addCustomer(LIST_QUEUE_NODE *head);

LIST_QUEUE_NODE *sortByNIF(LIST_QUEUE_NODE *head);

void SearchNIF(LIST_QUEUE_NODE *head);

#endif //PROJETO_LP_AED_CREATION_RESIZING_H
