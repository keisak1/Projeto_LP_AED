//
// Created by Nuno on 22/12/2021.
//

#include "csvData.h"


void bubbleSort(LIST_QUEUE_NODE *start) {
    int swapped, i;
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
    }
    while(swapped);
}

void swap(LIST_QUEUE_NODE *a, LIST_QUEUE_NODE *b) {
    LIST_QUEUE_NODE *temp;
    temp->customer = a->customer;
    a->customer = b->customer;
    b->customer = temp->customer;
}

LIST_QUEUE_NODE *nodeToCSV(LIST_QUEUE_NODE *head) {
    char *filename = "Data.csv";
    FILE *fp = fopen(filename, "w");
    while (head != NULL) {
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
        fprintf(fp, "\n");
        head = head->next;
    }
    fclose(fp);
}

LIST_QUEUE_NODE *appendnodeToCSV(LIST_QUEUE_NODE *tail) {
    char *filename = "Data.csv";
    FILE *fp = fopen(filename, "a");
    while (tail != NULL) {
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
        fprintf(fp, "\n");
        tail = tail->next;
    }
    fclose(fp);
}

LIST_QUEUE_NODE *csvToNode(char *token, char *row) {
    struct node *newNode = (struct node *) malloc(sizeof(LIST_QUEUE_NODE));
    newNode->customer.address = malloc(sizeof(char) * 100);
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
    newNode->customer.address = token;
    token = strtok(NULL, ";");
    newNode->customer.billingcost = atoi(token);
    return newNode;
}

void insertCustomerData(LIST_QUEUE_NODE *newNode) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Insert customer NIF:\n");
    scanf("%d", &newNode->customer.NIF);
    printf("Insert customer phone number:\n");
    scanf("%d", &newNode->customer.number);
    printf("Insert customer Birthday (Format: DAY-MONTH-YEAR):\n");
    scanf("%d", &newNode->customer.birthday.day);
    scanf("%d", &newNode->customer.birthday.month);
    scanf("%d", &newNode->customer.birthday.year);
    printf("Insert the address:\n");
    scanf("%s", newNode->customer.address);
    printf("Billing cost:");
    scanf("%d", &newNode->customer.billingcost);
    newNode->customer.registerdate.month = tm.tm_mon + 1;
    newNode->customer.registerdate.day = tm.tm_mday;
    newNode->customer.registerdate.year = tm.tm_year + +1900;
}