#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t *list = malloc(sizeof(*list));
    DIE(!list, "Malloc error");

    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    if (!list)
    	return NULL;

    dll_node_t *current = list->head;

    unsigned int index = 0;
    n = n % list->size;
    while (current && current->next && index < n) {
    	current = current->next;
    	++index;
    }

    return current;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
	if (!list)
		return;

	dll_node_t *current = list->head;
	unsigned int index = 0;
	while (current && current->next && index + 1 < n) {
		current = current->next;
		++index;
	}

	dll_node_t *new_node = malloc(sizeof(*new_node));
	DIE(!new_node, "Malloc error");
	new_node->data = malloc(list->data_size);
	DIE(!new_node->data, "Malloc error");
	memcpy(new_node->data, data, list->data_size);
	new_node->next = NULL;
	new_node->prev = NULL;

	dll_node_t *nextnode = NULL, *prevnode = NULL;
	if (n > 0) {
		if (current) {
			nextnode = current->next;
		} else {
			list->head = new_node;
            list->head->next = new_node;
            list->head->prev = new_node;
			list->size = 1;
			return;
		}

		current->next = new_node;
		if (nextnode)
			nextnode->prev = new_node;
		new_node->next = nextnode;
		new_node->prev = current;
	} else if (n == 0) {
		if (current) {
			prevnode = current->prev;
		} else {
			list->head = new_node;
            list->head->next = new_node;
            list->head->prev = new_node;
			list->size = 1;
			return;
		}

		current->prev = new_node;
		if (prevnode)
			prevnode->next = new_node;
		new_node->next = current;
		new_node->prev = prevnode;
		list->head = new_node;
	}
	list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    dll_node_t *next, *prev, *current, *removed;
    DIE(!list, "uninitialised list");

    if (n == 0) {
    	removed = list->head;
    	next = list->head->next;
    	prev = list->head->prev;
    	list->head = next;
    	list->head->prev = prev;
    	list->size--;
    } else if (n >= list->size) {
    	current = list->head;
    	unsigned int cnt = 0;
    	while (current && current->next && cnt < list->size - 2) {
    		cnt++;
    		current = current->next;
    	}
    	removed = current->next;
    	current->next = list->head;
    	list->size--;
    } else {
    	unsigned int cnt = 0;
    	current = list->head;
    	while (current && current->next && cnt < n - 1) {
    		cnt++;
    		current = current->next;
    	}
    	removed = current->next;
    	next = current->next->next;
    	prev = current;
    	current->next = next;
    	current->prev = prev;
    	list->size--;
    }

    return removed;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    dll_node_t *current, *temp;
	current = (*pp_list)->head;
	unsigned int index = 0;
    while (current && index < (*pp_list)->size) {
    	index++;
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
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    if (!list)
    	return;

    dll_node_t *current = list->head;
    unsigned int index = 0;
    while (current && index < list->size) {
    	index++;
    	printf("%d ", *(int *)current->data);
    	current = current->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
    if (!list)
    	return;

    dll_node_t *current = list->head;
    unsigned int index = 0;
    while (current && index < list->size) {
    	index++;
    	printf("%s ", current->data);
    	current = current->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_left_circular(dll_node_t* start)
{
    dll_node_t *current = start;
    
    printf("%d ", *(int *)current->data);
    current = current->prev;

    while (current != start) {
    	printf("%d ", *(int *)current->data);
    	current = current->prev;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_right_circular(dll_node_t* start)
{
    dll_node_t *current = start;

    printf("%d ", *(int *)current->data);
    current = current->next;

    while (current != start) {
    	printf("%d ", *(int *)current->data);
    	current = current->next;
    }

    printf("\n");
}

doubly_linked_list_t*
task2(doubly_linked_list_t* list1, doubly_linked_list_t* list2)
{
    doubly_linked_list_t *list3 = malloc(sizeof(*list3));
    DIE(!list3, "Malloc error");

    list3->head = NULL;
    list3->data_size = list1->data_size;
    list3->size = 0;

    unsigned int min = 1;
    if (list1->size < list2->size)
    	min = 2;

    dll_node_t *current1 = list1->head, *current2 = list2->head;
    unsigned int index = 0;
    while (current1 && current2 && index < list1->size && index < list2->size) {
    	index++;
    	int sum;
    	sum = *(int *)current1->data + *(int *)current2->data;
    	dll_add_nth_node(list3, index - 1, &sum);
    	current1 = current1->next;
    	current2 = current2->next;
    }

    if (min == 1) {
    	while (current2 && index < list2->size) {
    		index++;
    		dll_add_nth_node(list3, index - 1, current2->data);
    		current2 = current2->next;
    	}
    } else {
    	while (current1 && index < list1->size) {
    		index++;
    		dll_add_nth_node(list3, index - 1, current1->data);
    		current1 = current1->next;
    	}
    }

    return list3;
}
