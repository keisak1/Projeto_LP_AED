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
    printf("Removing the 4th position");
    if (trippos-1 < 0 || trippos-1 > head->customer.trips.arraySize) {
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


void searchCityByName(LIST_QUEUE_NODE *head) {

}