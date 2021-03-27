#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *next;
}Node;


int length(Node* head) {
    int index = 0;
    while (head) {
        head = head->next;
        index++;
    }

    return index;
}
    
void addLast(Node** head, int value) {
    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        exit(-1);
    new_node->value = value;

    if (!(*head)) {
        (*head) = new_node;
    }
    else {
        Node *current = *head;
        while (current && current->next)
            current = current->next;
        current->next = new_node;
    }
}

void split(Node* list, Node** oddList, Node** evenList) {
        // TODO1: trebuie sa facem o parcurgere a listei de la primul la
        // ultimul nod si sa mentinem si un contor sau ceva care sa ne
        // spuna daca suntem pe pozitie para sau impara.
        // TODO2: refolosim addLast al listelor primite ca parametri
        // pentru a le popula.

    int index = 1;
    Node *current = list;
    while (current) {
        if (index % 2 == 0)
            addLast(evenList, current->value);
        else
            addLast(oddList, current->value);

        index++;
        current = current->next;
    }
}

    void printList(Node* head) {
        Node* p = head;
        while (p != NULL) {
            printf("%d ", p->value);
            p = p->next;
        }
        printf("\n");
    }

int main() {

    // Pentru a va testa implementarea. Nu modificati.
    Node* list = NULL;

    addLast(&list, 1);
    addLast(&list, 2);
    addLast(&list, 3);
    addLast(&list, 4);
    addLast(&list, 5);
    addLast(&list, 6);
    addLast(&list, 7);
    printList(list);

    Node* oddList = NULL, *evenList = NULL;

    split(list, &oddList, &evenList);
    printList(list);
    printList(oddList);
    printList(evenList);

    Node* oddList1 = NULL, *evenList1 = NULL;
    split(evenList, &oddList1, &evenList1);
    printList(oddList1);
    printList(evenList1);

    Node* oddList2 = NULL, *evenList2 = NULL;
    split(evenList1, &oddList2, &evenList2);
    printList(evenList2);
    printList(oddList2);

    return 0;
}
