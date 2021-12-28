//
// Created by Nuno on 20/12/2021.
//

#include "creation_resizing.h"
#include "csvData.h"

LIST_QUEUE_NODE *sortByNIF(LIST_QUEUE_NODE *head) {
    printf("\n\nAdding sorted customer\n");
    head = addCustomer(head);
    bubbleSort(head);
    printList(head);
    nodeToCSV(head);
}

LIST_QUEUE_NODE *StoreCustomers() {
    char *filename = "Data.csv";
    char *token;
    char row[BUFFER_SIZE];
    fp = fopen(filename, "r");
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
    printf("\n\nAdding customer to head...\n");
    LIST_QUEUE_NODE *test = malloc(sizeof(LIST_QUEUE_NODE));
    test->customer.trips.arraySize = 3;
    test->customer.trips.citiesvisited = malloc(sizeof(int) * test->customer.trips.arraySize);
    test->customer.NIF = 123456789;
    test->customer.address = (char *) malloc(sizeof(char) * 100);
    test->customer.address = "Rua dos Camelos";
    test->customer.birthday.day = 25;
    test->customer.birthday.month = 04;
    test->customer.birthday.year = 1999;
    test->customer.billingcost = 40;
    test->customer.number = 915989016;
    test->customer.trips.citiesvisited[0] = 1;
    test->customer.trips.citiesvisited[1] = 2;
    test->customer.trips.citiesvisited[2] = 3;
    insertCustomerData(test);
    test->next = head;
    head = test;
    nodeToCSV(head);
    return head;
}

LIST_QUEUE_NODE *addCustomer(LIST_QUEUE_NODE *head) {
    LIST_QUEUE_NODE *test = malloc(sizeof(LIST_QUEUE_NODE));
    test->customer.trips.arraySize = 3;
    test->customer.trips.citiesvisited = malloc(sizeof(int) * test->customer.trips.arraySize);
    test->customer.address = malloc(sizeof(char) * 100);
    test->customer.NIF = 123456710;
    test->customer.address = "Rua dos Camelitos";
    test->customer.birthday.day = 25;
    test->customer.birthday.month = 04;
    test->customer.birthday.year = 1999;
    test->customer.billingcost = 40;
    test->customer.number = 915989016;
    test->customer.trips.citiesvisited[0] = 2;
    test->customer.trips.citiesvisited[1] = 3;
    test->customer.trips.citiesvisited[2] = 1;
    insertCustomerData(test);
    test->next = head;
    head = test;
    nodeToCSV(head);
    return head;
}

void addCustomerTail(LIST_QUEUE_NODE *tail) {
    printf("\nAdding customer to tail...\n");
    struct node *newNode = malloc(sizeof(LIST_QUEUE_NODE));
    newNode->customer.trips.arraySize = 3;
    newNode->customer.trips.citiesvisited = malloc(sizeof(int) * newNode->customer.trips.arraySize);
    newNode->customer.address = malloc(sizeof(char) * 100);
    newNode->customer.NIF = 987654321;
    newNode->customer.address = "Rua dos Bitoques";
    newNode->customer.birthday.day = 21;
    newNode->customer.birthday.month = 04;
    newNode->customer.birthday.year = 2010;
    newNode->customer.billingcost = 20;
    newNode->customer.number = 915989013;
    newNode->customer.trips.citiesvisited[0] = 2;
    newNode->customer.trips.citiesvisited[1] = 3;
    newNode->customer.trips.citiesvisited[2] = 1;
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
        printf("\nLinked list is empty\n");
    }
    printf("\nCustomer list\n");
    while (currentNode != NULL) {
        printf("%d ", currentNode->customer.NIF);
        printf("(");
        for (int i = 0; i < currentNode->customer.trips.arraySize; ++i) {
            printf(" %d ", currentNode->customer.trips.citiesvisited[i]);
        }
        printf(")");
        currentNode = currentNode->next;
    }
}

LIST_QUEUE_NODE *deleteCustomer(LIST_QUEUE_NODE *head) {
    struct node *temp;
    int NIF = 987654321;
    printf("\nDeleting the following NIF: %d\n", NIF);
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
                printf("\nCustomer deleted\n");
                break;
            } else
                current = current->next;
        }
    }
}

void SearchNIF(LIST_QUEUE_NODE *head) {
    struct node *temp = head;
    int NIF = 123456789;
    printf("\nSearching the following NIF: %d\n", NIF);
    while (temp != NULL) {
        if (temp->customer.NIF == NIF) {
            int length = temp->customer.trips.arraySize;
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
            printf("\nTrips: ");
            for (int i = 0; i < length; ++i) {
                printf("%d, ", temp->customer.trips.citiesvisited[i]);
            }
        }
        temp = temp->next;
    }
}

