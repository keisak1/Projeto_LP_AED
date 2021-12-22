//
// Created by Nuno on 20/12/2021.
//

#include "creation_resizing.h"

LIST_QUEUE_NODE *StoreCustomers() {
    char *filename = "Data.csv";
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
LIST_QUEUE_NODE *addCustomerHead(LIST_QUEUE_NODE *head) {
    struct node *newNode = malloc(sizeof(LIST_QUEUE_NODE));
    newNode->customer.address = malloc(sizeof(char) * 100);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Insert customer ID:\n");
    scanf("%d", &newNode->customer.ID);
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
    newNode->customer.registerdate.day = tm.tm_mday ;
    newNode->customer.registerdate.year = tm.tm_year+ + 1900;
    newNode->next = head;
    head = newNode;
   // head->next=NULL;
    nodeToCSV(head);
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

LIST_QUEUE_NODE * nodeToCSV(LIST_QUEUE_NODE *head){
    char *filename = "Data.csv";
    FILE *fp=fopen(filename,"a");
    while(head != NULL) {
        fprintf(fp, "%d;", head->customer.ID);
        fprintf(fp,"%d;", head->customer.number);
        fprintf(fp,"%d;",head->customer.birthday.day);
        fprintf(fp,"%d;",head->customer.birthday.month);
        fprintf(fp,"%d;",head->customer.birthday.year);
        fprintf(fp,"%d;",head->customer.registerdate.day);
        fprintf(fp,"%d;",head->customer.registerdate.month);
        fprintf(fp,"%d;",head->customer.registerdate.year);
        fprintf(fp,"%s;",head->customer.address);
        fprintf(fp,"%d;",head->customer.billingcost);
        fprintf(fp,"\n");
        head = head->next;
    }
}
