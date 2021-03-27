
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
}Node;

typedef struct List {
    Node *first;
    Node *last;
}List;

    void addLast(List* list, int value) {
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

    void print(List* list) {
        if (!list->first) {
            printf("List is empty\n");
            return;
        }
        Node *temp = list->first;
        while (temp) {
            printf("%d ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }

int list_size(List *l)
{
    Node *current = l->first;
    int index = 0;
    while(current) {
        index++;
        current = current->next;
    }

    return index;
}

List* merge(List *l1, List *l2) {

    List *list = malloc(sizeof(List));
    if (!list)
        exit(-1);
    list->first = NULL;
    list->last = NULL;

    Node *current1 = l1->first, *current2 = l2->first;
    int size1 = list_size(l1);
    int size2 = list_size(l2);
    int index1 = 0, index2 = 0;
    while(index1 < size1 && index2 < size2) {
        if (current1->value <= current2->value) {
            addLast(list, current1->value);
            index1++;
            current1 = current1->next;
        } else {
            addLast(list, current2->value);
            index2++;
            current2 = current2->next;
        }
    }
    while(index1 < size1) {
        addLast(list, current1->value);
        index1++;
        current1 = current1->next;
    }
    while(index2 < size2) {
        addLast(list, current2->value);
        index2++;
        current2 = current2->next;
    }
    
    return list;
}

int main() {
    List *l1, *l2;
    int m, n;
    int temp;
    
    l1 = calloc(1, sizeof(List));
    l2 = calloc(1, sizeof(List));
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        addLast(l1, temp);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &temp);
        addLast(l2, temp);
    }

    print(merge(l1, l2));

    return 0;
}
