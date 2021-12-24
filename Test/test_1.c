//
// Created by Nuno on 23/12/2021.
//

#include "test_1.h"


LIST_QUEUE_NODE test_1() {
    LIST_QUEUE_NODE *head = NULL;
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
}

