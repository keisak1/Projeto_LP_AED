//
// Created by Nuno on 23/12/2021.
//

#include "test_1.h"


LIST_QUEUE_NODE test_1() {
    int NIF_test = 123456789;
    POPULATION *population;
    LIST_QUEUE_NODE *head = NULL;
    CITYNODE *cityHead = NULL;
    head = StoreCustomers();
    head = addCustomerHead(head);
    addCustomerTail(head);
    printList(head);
    deleteCustomer(head);
    printList(head);
    SearchNIF(head);
    sortByNIF(head);
    editTrips(head);
    insertTrips(head);
    removeTrips(head);
    citiesToBin();
    cityHead = storeCity();
    searchCityByID(cityHead);
    editCityInfo(cityHead);
    insertPoI(cityHead);
    removePoI(cityHead);
    searchPoI(cityHead);
    searchUserTrip(head, cityHead, NIF_test);
    generateReport(head, cityHead);
    createPopulation(population,10);
    evaluate_fitness(cityHead, population, 10);
}

