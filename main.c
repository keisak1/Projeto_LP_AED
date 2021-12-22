#include <stdio.h>
#include "creation_resizing.h"

//LER FICHEIROS DE TEXTO E COLOCAR NOS PARAMETROS :))

int main() {
    LIST_QUEUE_NODE *head = NULL;
    CUSTOMER a;
    StoreCustomers();
    head = StoreCustomers();
    head = addCustomerHead(head, a);
    printList(head);
    return 0;
}
