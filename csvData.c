//
// Created by Nuno on 22/12/2021.
//

#include "csvData.h"


void bubbleSort(LIST_QUEUE_NODE *start) {
    int swapped;
    LIST_QUEUE_NODE *ptr1;
    LIST_QUEUE_NODE *ptr2 = NULL;
    if (start == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != ptr2) {
            if (ptr1->customer.NIF > ptr1->next->customer.NIF) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        ptr2 = ptr1;
    } while (swapped);
}

void swap(LIST_QUEUE_NODE *a, LIST_QUEUE_NODE *b) {
    struct node *temp = malloc(sizeof(LIST_QUEUE_NODE));
    temp->customer = a->customer;
    a->customer = b->customer;
    b->customer = temp->customer;
}

LIST_QUEUE_NODE *nodeToCSV(LIST_QUEUE_NODE *head) {
    char *filename = "Data.csv";
    fp = fopen(filename, "w");
    while (head != NULL) {
        int length = head->customer.trips.arraySize;
        fprintf(fp, "%d;", head->customer.NIF);
        fprintf(fp, "%d;", head->customer.number);
        fprintf(fp, "%d;", head->customer.birthday.day);
        fprintf(fp, "%d;", head->customer.birthday.month);
        fprintf(fp, "%d;", head->customer.birthday.year);
        fprintf(fp, "%d;", head->customer.registerdate.day);
        fprintf(fp, "%d;", head->customer.registerdate.month);
        fprintf(fp, "%d;", head->customer.registerdate.year);
        fprintf(fp, "%s;", head->customer.address);
        fprintf(fp, "%d;", head->customer.billingcost);
        for (int i = 0; i < length; ++i) {
            fprintf(fp, "%d", head->customer.trips.citiesvisited[i]);
        }
        fprintf(fp, ";");
        fprintf(fp, "\n");
        head = head->next;
    }
    fclose(fp);
}

LIST_QUEUE_NODE *appendnodeToCSV(LIST_QUEUE_NODE *tail) {
    char *filename = "Data.csv";
    fp = fopen(filename, "a");
    while (tail != NULL) {
        int length = tail->customer.trips.arraySize;
        fprintf(fp, "%d;", tail->customer.NIF);
        fprintf(fp, "%d;", tail->customer.number);
        fprintf(fp, "%d;", tail->customer.birthday.day);
        fprintf(fp, "%d;", tail->customer.birthday.month);
        fprintf(fp, "%d;", tail->customer.birthday.year);
        fprintf(fp, "%d;", tail->customer.registerdate.day);
        fprintf(fp, "%d;", tail->customer.registerdate.month);
        fprintf(fp, "%d;", tail->customer.registerdate.year);
        fprintf(fp, "%s;", tail->customer.address);
        fprintf(fp, "%d;", tail->customer.billingcost);
        for (int i = 0; i < length; ++i) {
            fprintf(fp, "%d", tail->customer.trips.citiesvisited[i]);
        }
        fprintf(fp, ";");
        fprintf(fp, "\n");
        tail = tail->next;
    }
    fclose(fp);
}

LIST_QUEUE_NODE *csvToNode(char *token, char *row) {
    struct node *newNode = (struct node *) malloc(sizeof(LIST_QUEUE_NODE));
    token = strtok(row, ";");
    newNode->customer.NIF = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.number = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.birthday.day = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.birthday.month = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.birthday.year = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.registerdate.day = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.registerdate.month = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.registerdate.year = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.address = (char *) malloc(sizeof(char) * (strlen(token) + 1));
    strncpy(newNode->customer.address,token,(strlen(token)+1));
    token = strtok(NULL, ";");
    newNode->customer.billingcost = atoi(token);
    token = strtok(NULL, ";");
    newNode->customer.trips.citiesvisited = malloc(sizeof(int) * strlen(token));
    newNode->customer.trips.arraySize = strlen(token);
    for (int i = 0; i < strlen(token); ++i) {
        char a = token[i];
        int temp = atoi(&a);
        newNode->customer.trips.citiesvisited[i] = temp;
    }
    return newNode;
}

void insertCustomerData(LIST_QUEUE_NODE *newNode) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int length = newNode->customer.trips.arraySize;
    printf("Insert customer NIF: %d\n", newNode->customer.NIF);
    printf("Insert customer phone number: %d\n", newNode->customer.number);
    printf("Insert customer Birthday (Format: DAY-MONTH-YEAR): %d/%d/%d\n", newNode->customer.birthday.day,
           newNode->customer.birthday.month, newNode->customer.birthday.year);
    printf("Insert the address: %s\n", newNode->customer.address);
    printf("Billing cost: %d\n", newNode->customer.billingcost);
    printf("Cities visited");
    for (int i = 0; i < length; ++i) {
        printf(" %d ", newNode->customer.trips.citiesvisited[i]);
    }
    printf("\n");
    newNode->customer.registerdate.month = tm.tm_mon + 1;
    newNode->customer.registerdate.day = tm.tm_mday;
    newNode->customer.registerdate.year = tm.tm_year + 1900;
}