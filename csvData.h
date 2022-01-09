//
// Created by Nuno on 22/12/2021.
//

#ifndef PROJETO_LP_AED_CSVDATA_H
#define PROJETO_LP_AED_CSVDATA_H

#include "creation_resizing.h"
/**
 * Transferir a informação do CSV para node.
 * @param token
 * @param row
 * @return
 */
LIST_QUEUE_NODE *csvToNode(char *token, char *row);
/**
 * Escrever dados da lista ligada para o ficheiro CSV.
 * @param head
 * @return
 */
LIST_QUEUE_NODE *nodeToCSV(LIST_QUEUE_NODE *head);
/**
 * Adiciona à cauda nova informação.
 * @param tail
 * @return
 */
LIST_QUEUE_NODE *appendnodeToCSV(LIST_QUEUE_NODE *tail);
/**
 * Função para inserir dados num cliente.
 * @param newNode
 */
void insertCustomerData(LIST_QUEUE_NODE *newNode);
/**
 * Função para fazer uma troca entre clientes.
 * @param a
 * @param b
 */
void swap(LIST_QUEUE_NODE *a, LIST_QUEUE_NODE *b);
/**
 * ordenação de clientes pelo NIF.
 * Complexidade temporal de O(n²).
 * @param start
 */
void bubbleSort(LIST_QUEUE_NODE *start);

#endif //PROJETO_LP_AED_CSVDATA_H
