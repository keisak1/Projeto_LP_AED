//
// Created by Nuno on 23/12/2021.
//

#ifndef PROJETO_LP_AED_TRIPSANDCITIES_H
#define PROJETO_LP_AED_TRIPSANDCITIES_H
#include "creation_resizing.h"
#include "csvData.h"


void editTrips(LIST_QUEUE_NODE *user);
void searchCityByName(LIST_QUEUE_NODE *head);
void insertTrips(LIST_QUEUE_NODE *head);
void removeTrips(LIST_QUEUE_NODE *head);
void citiesToBin();
CITYNODE *storeCity();
CITYNODE *binToNode(char *token, char *row);
CITYNODE *updateToBin(CITYNODE *head);
void searchCityByID(CITYNODE *head);
void searchPoI(CITYNODE *head);
void removePoI(CITYNODE *head);
void insertPoI(CITYNODE *head);
void editCityInfo(CITYNODE *user);
void searchUserTrip(LIST_QUEUE_NODE *head,CITYNODE *user, int NIF);
void generateReport(LIST_QUEUE_NODE *head, CITYNODE *user);


#endif //PROJETO_LP_AED_TRIPSANDCITIES_H
