// Copyright 2021 Adrian-Valeriu Croitoru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/student/Desktop/TEMA1/cdll.h"
#include "/home/student/Desktop/TEMA1/planet.h"
#include "/home/student/Desktop/TEMA1/operations.h"

void
add(doubly_linked_list_t *galaxy, char name[], int index, int shields)
{
	if ((unsigned int)index > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	planet *added_planet = malloc(sizeof(planet));
	snprintf(added_planet->name, strlen(name) + 1, "%s", name);
	added_planet->kills = 0;
	added_planet->shield = dll_create(sizeof(int));
	for (int i = 0; i < shields; i++) {
		int shield_value = 1;
		dll_add_nth_node(added_planet->shield, (unsigned int)i, &shield_value);
	}

	dll_add_nth_node(galaxy, (unsigned int)index, added_planet);
	free(added_planet);  /* intrucat s-a dat memcpy in dll_add_nth_node */

	printf("The planet %s has joined the galaxy.\n", name);
}

void
blh(doubly_linked_list_t *galaxy, int index, int mode)
{
	if ((unsigned int)index + 1 > galaxy->size || galaxy->size == 0) {
		printf("Planet out of bounds!\n");
		return;
	}

	/* se obtine adresa planetei de eliminat si se da free la memorie */
	dll_node_t *removed_planet = dll_rm_nth_node(galaxy, (unsigned int)index);
	planet *removed_planet_data = (planet *)removed_planet->data;
	if (mode)
		printf("The planet %s has been eaten by the vortex.\n",
			   removed_planet_data->name);

	dll_free(&removed_planet_data->shield);
	free(removed_planet->data);
	free(removed_planet);
}

void
upg(doubly_linked_list_t *galaxy, int index, int shield, int value)
{
	if ((unsigned int)index + 1 > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *current_planet = dll_get_nth_node(galaxy, (unsigned int)index);
	planet *current_planet_data = (planet *)current_planet->data;
	unsigned int planet_shield_number = current_planet_data->shield->size;
	if ((unsigned int)shield + 1 > planet_shield_number) {
		printf("Shield out of bounds!\n");
		return;
	}

	dll_node_t *current_shield = dll_get_nth_node(current_planet_data->shield,
												  shield);

	/* se upgradeaza valoarea efectiva a scutului */
	int *current_shield_value = current_shield->data;
	*current_shield_value = (*current_shield_value) + value;
	memcpy(current_shield->data, current_shield_value, sizeof(int));
}

void
exp_a(doubly_linked_list_t *galaxy, int index, int shield_value)
{
	if ((unsigned int)index + 1 > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *current_planet = dll_get_nth_node(galaxy, (unsigned int)index);
	planet *current_planet_data = (planet *)current_planet->data;

	int temp_index = current_planet_data->shield->size;
	dll_add_nth_node(current_planet_data->shield, temp_index, &shield_value);
}

void
rmv(doubly_linked_list_t *galaxy, int planet_index, int shield_index)
{
	if ((unsigned int)planet_index + 1 > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *current_planet = dll_get_nth_node(galaxy,
												  (unsigned int)planet_index);
	planet *current_planet_data = (planet *)current_planet->data;

	unsigned int planet_shield_number = current_planet_data->shield->size;
	if ((unsigned int)shield_index  + 1 > planet_shield_number) {
		printf("Shield out of bounds!\n");
		return;
	} else if (planet_shield_number < 5) {
		printf("A planet cannot have less than 4 shields!\n");
		return;
	}

	dll_node_t *removed_shield = dll_rm_nth_node(current_planet_data->shield,
												 shield_index);
	free(removed_shield->data);
	free(removed_shield);
}

void
col(doubly_linked_list_t *galaxy, int index1, int index2)
{
	if ((unsigned int)index2 + 1 > galaxy->size ||
		(unsigned int)index1 + 1 > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}
	/* se acceseaza datele din cele doua planete,
	   iar apoi se retin adresele celor doua scuturi ce urmeaza
	   a se ciocni */
	dll_node_t *current_planet1 = dll_get_nth_node(galaxy,
												   (unsigned int)index1);
	planet *current_planet_data1 = (planet *)current_planet1->data;
	dll_node_t *current_planet2 = dll_get_nth_node(galaxy,
												   (unsigned int)index2);
	planet *current_planet_data2 = (planet *)current_planet2->data;
	doubly_linked_list_t *shield1 = current_planet_data1->shield;
	doubly_linked_list_t *shield2 = current_planet_data2->shield;
	dll_node_t *col_shield1 = dll_get_nth_node(shield1, shield1->size / 4);
	dll_node_t *col_shield2 = dll_get_nth_node(shield2,
											   (shield2->size / 4) * 3);

	/* se updateaza valorile scuturilor dupa ciocnire */
	int *col_shield1_value = col_shield1->data;
	int *col_shield2_value = col_shield2->data;
	*col_shield1_value = *col_shield1_value - 1;
	*col_shield2_value = *col_shield2_value - 1;
	memcpy(col_shield1->data, col_shield1_value, sizeof(int));
	memcpy(col_shield2->data, col_shield2_value, sizeof(int));

	/* se verifica daca vreo planeta a implodat,
	   iar in caz pozitiv se elimina din galaxie */
	if (*col_shield1_value < 0) {
		if (*col_shield2_value < 0) {
			printf("The planet %s has imploded.\n",
				   current_planet_data1->name);
			printf("The planet %s has imploded.\n",
				   current_planet_data2->name);
			blh(galaxy, index2, 0);
			blh(galaxy, index1, 0);
		} else {
			printf("The planet %s has imploded.\n",
				   current_planet_data1->name);
			blh(galaxy, index1, 0);
			if (current_planet_data2)
				current_planet_data2->kills = current_planet_data2->kills + 1;
		}
	} else if (*col_shield2_value < 0) {
		printf("The planet %s has imploded.\n", current_planet_data2->name);
		blh(galaxy, index2, 0);
		if (current_planet_data1)
			current_planet_data1->kills = current_planet_data1->kills + 1;
	}
}

void
rot(doubly_linked_list_t *galaxy, int index, char mode, int units)
{
	if ((unsigned int)index + 1 > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *current_planet = dll_get_nth_node(galaxy, (unsigned int)index);
	planet *current_planet_data = (planet *)current_planet->data;
	doubly_linked_list_t *current_planet_shd = current_planet_data->shield;

	/* pentru a nu cicla de mai multe ori decat este nevoie lista circulara */
	if (current_planet_shd->size > 0)
		units = units % (current_planet_shd->size);

	if (mode == 99) {  /* ciclare la dreapta */
		for (int i = 0; i < units; i++) {
			dll_node_t *last = dll_get_nth_node(current_planet_shd,
												current_planet_shd->size - 1);
			current_planet_shd->head = last;
		}
	} else if (mode == 116) {  /* ciclare la stanga */
		for (int i = 0; i < units; i++)
			current_planet_shd->head = current_planet_shd->head->next;
	} else {
		printf("Not a valid direction!\n");
		return;
	}
}

void
shw(doubly_linked_list_t *galaxy, int index)
{
	if ((unsigned int)index + 1 > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	dll_node_t *current_planet = dll_get_nth_node(galaxy, (unsigned int)index);
	planet *current_planet_data = (planet *)current_planet->data;

	dll_node_t *next_planet, *prev_planet;
	next_planet = current_planet->next;
	prev_planet = current_planet->prev;
	planet *next_planet_data = (planet *)next_planet->data;
	planet *prev_planet_data = (planet *)prev_planet->data;

	printf("NAME: %s\n", current_planet_data->name);
	printf("CLOSEST: ");
	if (galaxy->size == 1)
		printf("none\n");
	else if (galaxy->size == 2)
		printf("%s\n", next_planet_data->name);
	else
		printf("%s and %s\n", prev_planet_data->name, next_planet_data->name);
	printf("SHIELDS: ");
	dll_print_int_list(current_planet_data->shield);
	printf("Killed: %d\n", current_planet_data->kills);
}
