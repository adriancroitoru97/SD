#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));
    DIE(!list, "malloc error");

    list->size = 0;
    list->data_size = data_size;
    list->head = NULL;

    return list;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
	ll_node_t *current, *next, *new_node;
	DIE(!list, "uninitialised list");

    new_node = (ll_node_t *)malloc(sizeof(ll_node_t));
    DIE(!new_node, "malloc error");
    new_node->data = malloc(list->data_size);
    DIE(!new_node->data, "malloc error");
    memcpy(new_node->data, new_data, list->data_size);

    if (n == 0) {
    	new_node->next = list->head;
    	list->head = new_node;
    	list->size++;
    } else if (n >= list->size) {
    	new_node->next = NULL;
    	current = list->head;
    	while (current != NULL && current->next != NULL)
    		current = current->next;

    	if (current != NULL)
    		current->next = new_node;
    	else 
    		list->head = new_node;

    	list->size++; 
    } else {
    	unsigned int cnt = 0;
    	current = list->head;
    	while (cnt < n - 1) {
    		cnt++;
    		current = current->next;
    	}
    	next = current->next;
    	current->next = new_node;
    	new_node->next = next;
    	list->size++; 
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
	ll_node_t *next, *current, *removed;
    DIE(!list, "uninitialised list");

    if (n == 0) {
    	removed = list->head;
    	next = list->head->next;
    	list->head = next;
    	list->size--;
    } else if (n >= list->size - 1) {
    	unsigned int cnt = 0;
    	current = list->head;
    	while (cnt < list->size - 2) {
    		cnt++;
    		current = current->next;
    	}
    	removed = current->next;
    	current->next = NULL;
    	list->size--;
    } else {
    	unsigned int cnt = 0;
    	current = list->head;
    	while (cnt < n) {
    		cnt++;
    		current = current->next;
    	}
    	removed = current;
    	next = current->next;
    	current->next = next->next;
    	list->size--;
    }

    return removed;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void
ll_free(linked_list_t** pp_list)
{
	ll_node_t *current, *temp;
	current = (*pp_list)->head;
    for (int i = 0; i < (int)(*pp_list)->size; i++) {
    	free(current->data);
    	temp = current->next;
    	free(current);
    	current = temp;
    }
    free(*(pp_list));
    (*pp_list) = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    ll_node_t *current;
	current = list->head;
	for (int i = 0; i < (int)list->size; i++) {
		printf("%d ", *(int*)current->data);
		current = current->next;
	}
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    ll_node_t *current;
	current = list->head;
    for (int i = 0; i < (int)list->size; i++) {
    	printf("%s ", current->data);
    	current = current->next;
    }

    printf("\n");
}
