//
// Created by Nuno on 22/12/2021.
//

#include "csvData.h"


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

LIST_QUEUE_NODE *apeendnodeToCSV(LIST_QUEUE_NODE *tail) {
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