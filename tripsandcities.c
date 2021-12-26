//
// Created by Nuno on 23/12/2021.
//

#include "tripsandcities.h"


void editTrips(LIST_QUEUE_NODE *user) {
    printf("\nEditing trip:\n");
    printf("%d", user->customer.trips.citiesvisited[0]);
    printf("\nEdited to: ");
    user->customer.trips.citiesvisited[0] = 8;
    printf("%d", user->customer.trips.citiesvisited[0]);
    nodeToCSV(user);

}

void insertTrips(LIST_QUEUE_NODE *head) {
    printf("\n\nResizing and inserting new trips");
    printf("\nBefore:\n");
    for (int i = 0; i < head->customer.trips.arraySize; ++i) {
        printf("%d ", head->customer.trips.citiesvisited[i]);
    }
    head->customer.trips.arraySize = 5;
    head->customer.trips.citiesvisited = realloc(head->customer.trips.citiesvisited,
                                                 sizeof(int) * head->customer.trips.arraySize);
    head->customer.trips.citiesvisited[3] = 7;
    head->customer.trips.citiesvisited[4] = 8;
    printf("\n After: \n");
    for (int i = 0; i < head->customer.trips.arraySize; ++i) {
        printf("%d ", head->customer.trips.citiesvisited[i]);
    }
    nodeToCSV(head);
}

void removeTrips(LIST_QUEUE_NODE *head) {
    printf("\n\nRemoving a trip by its position in the array");
    int trippos = 5;
    printf("Removing the 5th position");
    if (trippos - 1 < 0 || trippos - 1 > head->customer.trips.arraySize) {
        printf("Invalid position! Please enter position between 1 to %d", head->customer.trips.arraySize);
    }
    for (int i = trippos - 1; i < head->customer.trips.arraySize; ++i) {
        head->customer.trips.citiesvisited[trippos] = head->customer.trips.citiesvisited[trippos + 1];
    }
    head->customer.trips.arraySize--;
    for (int i = 0; i < head->customer.trips.arraySize; ++i) {
        printf("%d ", head->customer.trips.citiesvisited[i]);
    }
    nodeToCSV(head);
}

void citiesToBin() {
    char *filename = "City.bin";
    FILE *fptr = fopen(filename, "wb");
    char *text = "1,Braga,Belas praias,3.0,1.0,3,4,2,\n2,Porto,Belas praias,1.0,2.0,4,2,1,\n3,Aveiro,Belas praias,0.0,1.0,6,1,2,\n4,Guimaraes,Belas praias,2.0,0.0,0,2,4,\n5,Lisboa,Belas praias,5.0,0.1,3,4,5,\n6,Albufeira,Belas praias,3.0,5.0,6,1,1,\n7,Coimbra,Belas praias,0.0,5.0,6,6,6,\n8,Guarda,Belas praias,6.0,5.0,4,1,4,\n9,Chaves,Belas praias,7.0,4.0,2,3,4,\n10,Leiria,Belas praias,8.0,4.0,4,1,3,";
    fwrite(text, strlen(text) + 1, 1, fptr);
    fclose(fptr);
}

CITYNODE *storeCity() {
    char *token;
    char row2[BUFFER_SIZE];
    FILE *fptr = fopen("City.bin", "rb");
    if (fptr == NULL) {
        printf("Error: could not open file");
    }
    struct cityNode *newNode;
    struct cityNode *prevNode;
    CITYNODE *head;

    // For first iteration
    fgets(row2, BUFFER_SIZE, fptr);
    prevNode = binToNode(token, row2);
    head = prevNode;

    // 2-nth
    while (fgets(row2, BUFFER_SIZE, fptr)) {
        //1 Make next Node
        //2 Link next to newNode
        //3 make it prevNode
        newNode = binToNode(token, row2);
        prevNode->nextcity = newNode;
        prevNode = newNode;
        prevNode->nextcity = NULL;
    }
    fclose(fptr);
    return head;
}

CITYNODE *binToNode(char *token, char *row) {
    struct cityNode *newNode = (struct cityNode *) malloc(sizeof(CITYNODE));
    token = strtok(row, ",");
    newNode->city.ID = atoi(token);
    token = strtok(row, ",");
    newNode->city.name = (char *) malloc(sizeof(char) * strlen(token));
    newNode->city.name = token;
    token = strtok(row, ",");
    newNode->city.description = (char *) malloc(sizeof(char) * strlen(token));
    newNode->city.description = token;
    token = strtok(row, ",");
    newNode->city.x = atof(token);
    token = strtok(row, ",");
    newNode->city.y = atof(token);
    token = strtok(row, ",");
    newNode->city.PoI.beaches = atoi(token);
    token = strtok(row, ",");
    newNode->city.PoI.museums = atoi(token);
    token = strtok(row, ",");
    newNode->city.PoI.parks = atoi(token);

    return newNode;
}

void searchCityByName(LIST_QUEUE_NODE *head) {

}