//
// Created by Nuno on 20/12/2021.
//

#include "creation_resizing.h"
#include "csvData.h"

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
        prevNode->next = NULL;
    }
    fclose(fp);
    return head;
}

LIST_QUEUE_NODE *addCustomerHead(LIST_QUEUE_NODE *head) {
    struct node *newNode = malloc(sizeof(LIST_QUEUE_NODE));
    newNode->customer.address = malloc(sizeof(char) * 100);
    insertCustomerData(newNode);
    newNode->next = head;
    head = newNode;
    nodeToCSV(head);
    return head;
}

void addCustomerTail(LIST_QUEUE_NODE *tail) {
    struct node *newNode = malloc(sizeof(LIST_QUEUE_NODE));
    newNode->customer.address = malloc(sizeof(char) * 100);
    insertCustomerData(newNode);
    struct node *lastNode = tail;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    lastNode->next->next = NULL;
    appendnodeToCSV(lastNode->next);
}


void printList(LIST_QUEUE_NODE *head) {
    LIST_QUEUE_NODE *currentNode = head;
    if (head == NULL) {
        printf("Linked list is empty");
    }
    while (currentNode != NULL) {
        printf("%d ", currentNode->customer.NIF);
        currentNode = currentNode->next;
    }
}

LIST_QUEUE_NODE *deleteCustomer(LIST_QUEUE_NODE *head) {
    struct node *temp;
    int NIF = 0;
    printf("Insert the customer NIF you want to delete:\n");
    scanf("%d", &NIF);
    if (head->customer.NIF == NIF) {
        temp = head;
        head = head->next;
        free(temp);
    } else {
        struct node *current = head;
        while (current->next != NULL) {
            if (current->next->customer.NIF == NIF) {
                temp = current->next;
                //node will be disconnected from the linked list.
                current->next = current->next->next;
                free(temp);
                printf("Customer deleted\n");
                break;
            } else
                current = current->next;
        }
    }
}

void SearchNIF(LIST_QUEUE_NODE *head) {
    struct node *temp = head;
    int NIF = 0;
    printf("Insert the customer NIF you want to search:\n");
    scanf("%d", &NIF);
    while (temp != NULL) {
        if (temp->customer.NIF == NIF) {
            printf("%d;", temp->customer.NIF);
            printf("%d;", temp->customer.number);
            printf("%d;", temp->customer.birthday.day);
            printf("%d;", temp->customer.birthday.month);
            printf("%d;", temp->customer.birthday.year);
            printf("%d;", temp->customer.registerdate.day);
            printf("%d;", temp->customer.registerdate.month);
            printf("%d;", temp->customer.registerdate.year);
            printf("%s;", temp->customer.address);
            printf("%d;", temp->customer.billingcost);
        }
        temp = temp->next;
    }
    printf("NIF not existent");
}


void CreateAndResizeArrayTrips(LIST_QUEUE_NODE *head, int numberoftrips) {
    if (head->customer.trips == NULL) {
        head->customer.trips = malloc(sizeof(char) * numberoftrips);
        head->customer.NumberOfTrips = numberoftrips;
    } else {
        head->customer.trips = realloc(head->customer.trips, sizeof(char) * numberoftrips);
        head->customer.NumberOfTrips = numberoftrips;
    }
}