#include <stdio.h>
#include "creation_resizing.h"

//LER FICHEIROS DE TEXTO E COLOCAR NOS PARAMETROS :))

int main() {
    LIST_QUEUE_NODE *head = NULL;
    CUSTOMER a;
    StoreCustomers();
    //addCustomerHead(head, a);
    printList(StoreCustomers());
    return 0;
}
