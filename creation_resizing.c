//
// Created by Nuno on 20/12/2021.
//

#include "creation_resizing.h"

LIST_QUEUE_NODE *StoreCustomers() {
    char *filename = "Data.txt";
    char *token;
    char row[BUFFER_SIZE];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s", filename);
    }
    struct node *newNode;
    struct node *prevNode;
    LIST_QUEUE_NODE *head;

    // For first iteration
    fgets(row, BUFFER_SIZE, fp);
    prevNode = csvToNode(token, row);
    head = prevNode;

    // 2-nth
    while (fgets(row, BUFFER_SIZE, fp)) {
        //1 Make next Node
        //2 Link next to newNode
        //3 make it prevNode
        newNode = csvToNode(token, row);
        prevNode->next = newNode;
        prevNode = newNode;
        prevNode->next=NULL;
    }
    fclose(fp);
    return head;
}

LIST_QUEUE_NODE *addCustomerHead(LIST_QUEUE_NODE *head, struct customer a) {
    struct node *newNode = malloc(sizeof(LIST_QUEUE_NODE));
    a.address = malloc(sizeof(char) * 100);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Insert customer ID:");
    scanf("%d", &a.ID);
    printf("Insert customer phone number:");
    scanf("%d", &a.number);
    printf("Insert customer Birthday (Format: DAY-MONTH-YEAR)");
    scanf("%d", &a.birthday.day);
    scanf("%d", &a.birthday.month);
    scanf("%d", &a.birthday.year);
    printf("Insert the address");
    scanf("%s", a.address);
    printf("Billing cost:");
    scanf("%d", &a.billingcost);
    newNode->customer.registerdate.month = tm.tm_mon + 1;
    newNode->customer.registerdate.day = tm.tm_mday + 1900;
    newNode->customer.registerdate.year = tm.tm_year;
    newNode->customer.ID = a.ID;
    newNode->customer.number = a.number;
    newNode->customer.billingcost = a.billingcost;
    newNode->customer.birthday.day = a.birthday.day;
    newNode->customer.birthday.month = a.birthday.month;
    newNode->customer.birthday.year = a.birthday.year;
    newNode->next = head;
    head = newNode;

    return head;
}

void printList(LIST_QUEUE_NODE *head) {
    LIST_QUEUE_NODE *currentNode = head;
    if (head == NULL) {
        printf("Linked list is empty");
    }
    while (currentNode != NULL) {
        printf("%d ", currentNode->customer.ID);
        currentNode = currentNode->next;
    }
}


LIST_QUEUE_NODE * csvToNode(char *token, char* row) {
    struct node *newNode = (struct node *) malloc(sizeof(LIST_QUEUE_NODE));
    newNode->customer.address = malloc(sizeof(char) * 100);
    token = strtok(row, ";");
    newNode->customer.ID = atoi(token);
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