//
// Created by Nuno on 20/12/2021.
//

#ifndef PROJETO_LP_AED_CREATION_RESIZING_H
#define PROJETO_LP_AED_CREATION_RESIZING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define BUFFER_SIZE 1024
FILE *fp;

typedef struct city {
    int ID;
    char *name;
    char *description;
    float x, y;
    struct poi {
        int beaches, museums, parks;
    } PoI;
} CITY;

typedef struct cityNode {
    CITY city;
    struct cityNode *nextcity;
} CITYNODE;

typedef struct trips {
    int arraySize;
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


/**
 * Guarda a informação do cliente, carregada pelo ficheiro CSV para uma estrutura com lista ligada.
 * @return
 */
LIST_QUEUE_NODE *StoreCustomers();
/**
 * * Adiciona um cliente à cabeça da lista ligada, se o NIF do cliente já existir, não alterará a lista ligada.
 * Se não existir tal cliente, adicionará à cabeça do node e irá atualizar o ficheiro CSV.
 * @param head
 * @return
 */
LIST_QUEUE_NODE *addCustomerHead(LIST_QUEUE_NODE *head);

/**
* Insere cliente à cauda, se já existir, não altera a lista ligada, se não for esse o caso irá atualizar a lista ligada e o ficheiro CSV.
 * @param tail
 */
void addCustomerTail(LIST_QUEUE_NODE *tail);
/**
 * Imprime a lista ligada com os clientes.
 */
void printList(LIST_QUEUE_NODE *head);
/**
 * Elimina um cliente, desconectando o node da lista ligada
 * @param head
 * @return
 */
LIST_QUEUE_NODE *deleteCustomer(LIST_QUEUE_NODE *head);

LIST_QUEUE_NODE *addCustomer(LIST_QUEUE_NODE *head);

/**
 * Ordena por NIF
 * @param head
 * @return
 */
LIST_QUEUE_NODE *sortByNIF(LIST_QUEUE_NODE *head);
/**
 * procura por um NIF existente na lista ligada e imprime o cliente.
 * @param head
 */
void SearchNIF(LIST_QUEUE_NODE *head);

#endif //PROJETO_LP_AED_CREATION_RESIZING_H
