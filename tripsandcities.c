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

CITYNODE *updateToBin(CITYNODE *head) {
    char *filename = "City.bin";
    FILE *fptr = fopen(filename, "wb");
    while (head != NULL) {
        char *comma = ",";
        char *nextline = "\n";
        int ID = head->city.ID;
        fwrite(&ID, sizeof(ID), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);
        char *name = head->city.name;
        fwrite(name, strlen(name), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);
        char *description = head->city.description;
        fwrite(description, strlen(description), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);

        float x = head->city.x;
        fwrite(&x, sizeof(x), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);


        float y = head->city.y;
        fwrite(&y, sizeof(y), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);

        int beaches = head->city.PoI.beaches;
        fwrite(&beaches, sizeof(beaches), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);

        int museums = head->city.PoI.museums;
        fwrite(&museums, sizeof(museums), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);

        int parks = head->city.PoI.parks;
        fwrite(&parks, sizeof(parks), 1, fptr);
        fwrite(comma, strlen(comma), 1, fptr);
        fwrite(nextline, strlen(nextline), 1, fptr);
        head = head->nextcity;
    }
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


void searchCityByID(CITYNODE *head) {
    struct cityNode *temp = (struct cityNode *) head;
    int ID = 3;
    printf("\nSearching the following city ID: %d\n", ID);
    while (temp != NULL) {
        if (temp->city.ID == ID) {
            printf("%d\n", temp->city.ID);
            printf("%s\n", temp->city.name);
            printf("%s\n", temp->city.description);
            printf("Coordinates: ");
            printf("%f", temp->city.x);
            printf(" %f\n", temp->city.y);
            printf("Number of beaches: %d\n", temp->city.PoI.beaches);
            printf("Number of museums: %d\n", temp->city.PoI.museums);
            printf("Number of parks: %d\n", temp->city.PoI.parks);
        }
        temp = temp->nextcity;
    }
}

void editCityInfo(CITYNODE *user) {
    printf("\nEditing city description:\n");
    printf("%s", user->city.description);
    printf("\nEdited to: ");
    user->city.description = "Perfect park for picnics";
    printf("%s", user->city.description);
    updateToBin(user);
}

void insertPoI(CITYNODE *head) {
    printf("\n\nResizing and inserting new points of interest");
    printf("\nBefore:\n");
    printf("Number of beaches: %d", head->city.PoI.beaches);
    printf("Number of beaches: %d", head->city.PoI.museums);
    printf("Number of beaches: %d", head->city.PoI.parks);
    head->city.PoI.beaches++;
    head->city.PoI.museums++;
    head->city.PoI.parks++;
    printf("\n After: \n");
    printf("Number of beaches: %d", head->city.PoI.beaches);
    printf("Number of beaches: %d", head->city.PoI.museums);
    printf("Number of beaches: %d", head->city.PoI.parks);
    updateToBin(head);
}

void removePoI(CITYNODE *head) {
    printf("\n\nRemoving points of interest");
    printf("\nBefore:\n");
    printf("Number of beaches: %d", head->city.PoI.beaches);
    printf("Number of beaches: %d", head->city.PoI.museums);
    printf("Number of beaches: %d", head->city.PoI.parks);
    head->city.PoI.beaches--;
    head->city.PoI.museums--;
    head->city.PoI.parks--;
    printf("\n After: \n");
    printf("Number of beaches: %d", head->city.PoI.beaches);
    printf("Number of museums: %d", head->city.PoI.museums);
    printf("Number of parks: %d", head->city.PoI.parks);
    updateToBin(head);
}

void searchPoI(CITYNODE *head) {
    struct cityNode *temp = (struct cityNode *) head;
    int ID = 1;
    printf("\n\nSearching the following city ID: %d", ID);
    while (temp != NULL) {
        if (temp->city.ID == ID) {
            printf("Number of beaches: %d\n", temp->city.PoI.beaches);
            printf("Number of museums: %d\n", temp->city.PoI.museums);
            printf("Number of parks: %d\n", temp->city.PoI.parks);
        }
        temp = temp->nextcity;
    }
}

void searchUserTrip(LIST_QUEUE_NODE *head, CITYNODE *user, int NIF) {

    while (head != NULL) {
        if (head->customer.NIF == NIF) {
            for (int i = 0; i < head->customer.trips.arraySize; ++i) {
                if (head->customer.trips.citiesvisited[i] == user->city.ID) {
                    printf("\n%s\n", user->city.name);
                    printf("Beaches: %d\n", user->city.PoI.beaches);
                    printf("Museums: %d\n", user->city.PoI.museums);
                    printf("Parks: %d\n", user->city.PoI.parks);
                }
            }
            head = head->next;
        }
    }
}

void generateReport(LIST_QUEUE_NODE *head, CITYNODE *city){
    char *filename = "Report.txt";
    fp = fopen(filename, "w");
    while (head != NULL) {
        int length = head->customer.trips.arraySize;
        fprintf(fp, "NIF: %d\n", head->customer.NIF);
        fprintf(fp, "Phone: %d\n", head->customer.number);
        fprintf(fp, "Birthday: %d/%d/%d\n", head->customer.birthday.day, head->customer.birthday.month, head->customer.birthday.year);
        fprintf(fp, "Register Date: %d/%d/%d\n", head->customer.registerdate.day, head->customer.registerdate.month, head->customer.registerdate.year);
        fprintf(fp, "Address: %s\n", head->customer.address);
        fprintf(fp, "Billing Cost: %d\n", head->customer.billingcost);
        printf("Trips: ");
        for (int i = 0; i < length; ++i) {
            while(city != NULL) {
                if(head->customer.trips.citiesvisited[i] == city->city.ID) {
                    printf("%s", city->city.name);
                    fprintf(fp, "%d, ", head->customer.trips.citiesvisited[i]);
                }
                printf("\nBeaches: %d\n", city->city.PoI.beaches);
                printf("\nMuseums: %d\n", city->city.PoI.museums);
                printf("\nParks: %d\n", city->city.PoI.parks);
                city = city->nextcity;
            }
        }
        fprintf(fp, ";");
        fprintf(fp, "\n");
        head = head->next;
    }
    fclose(fp);

}
