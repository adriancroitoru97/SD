
	#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
}Node;

typedef struct LinkedList {
    Node *first;
    Node *last;
}LinkedList;

    void addLast(LinkedList* list, int value) {
        if (!list->first) {
            list->first = calloc(1, sizeof(Node));
            list->first->value = value;
            list->last = list->first;
        } else {
            Node *temp = calloc(1, sizeof(Node));
            temp->value = value;
            list->last->next = temp;
            list->last = temp;
        }
    }

void printNumber(Node* node) {
    if (!node) {
         return;
    }

      printNumber(node->next);
      printf("%d",node->value);
}


LinkedList* addNumbers(LinkedList *l1, LinkedList *l2) {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (!list)
        exit(-1);
    list->first = NULL;
    list->last = NULL;

    Node *current1 = l1->first, *current2 = l2->first;
    //int index1 = 0, index2 = 0, index = 0;
    int transport = 0, cifra_curenta = 0;
    while (current1 && current2) {
        cifra_curenta = current1->value + current2->value + transport;
        transport = 0;
        transport += cifra_curenta / 10;
        cifra_curenta %= 10;

        addLast(list, cifra_curenta);

        //index++;
        current1 = current1->next;
        current2 = current2->next;
    }

    while (current1) {
        cifra_curenta = current1->value + transport;
        transport = 0;
        cifra_curenta %= 10;

        addLast(list, cifra_curenta);
        current1 = current1->next;
    }

    while (current2) {
        cifra_curenta = current2->value + transport;
        transport = 0;
        cifra_curenta %= 10;

        addLast(list, cifra_curenta);
        current2 = current2->next;
    }




    return list;
}

int main() {
    int n, m, value;
    LinkedList *a, *b, *result;
    
    a = calloc(1, sizeof(LinkedList));
    b = calloc(1, sizeof(LinkedList));
    
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &value);
        addLast(a, value);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &value);
        addLast(b, value);
    }

    printNumber(addNumbers(a, b)->first);

    return 0;
}
