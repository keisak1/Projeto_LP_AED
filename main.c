#include <stdio.h>
#include "creation_resizing.h"

//LER FICHEIROS DE TEXTO E COLOCAR NOS PARAMETROS :))

int main() {
    LIST_QUEUE_NODE *head = NULL;
    StoreCustomers();
    head = StoreCustomers();
    head = addCustomerHead(head);
    printList(head);
    return 0;
}