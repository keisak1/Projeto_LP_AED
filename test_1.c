//
// Created by Nuno on 23/12/2021.
//

#include "test_1.h"


LIST_QUEUE_NODE test_1() {
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
    searchUserTrip(head, cityHead, 123456789);
    generateReport(head, cityHead);
}

