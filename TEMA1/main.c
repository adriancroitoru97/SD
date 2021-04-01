// Copyright 2021 Adrian-Valeriu Croitoru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdll.h"
#include "planet.h"
#include "operations.h"

#define MSL 255  /* MAX_STRING_LENGTH */

int main() {
    int nr_operations = 0;
    doubly_linked_list_t *galaxy = dll_create(sizeof(planet));

    scanf("%d", &nr_operations);
    for (int i = 0; i < nr_operations; i++) {
        char operation[MSL];
        scanf("%s", operation);
        if (strcmp(operation, "ADD") == 0) {
            char planet_name[MSL];
            int planet_index, planet_shields;
            scanf("%s %d %d", planet_name, &planet_index, &planet_shields);
            add(galaxy, planet_name, planet_index, planet_shields);
        }
        if (strcmp(operation, "BLH") == 0) {
            int planet_index;
            scanf("%d", &planet_index);
            blh(galaxy, planet_index, 1);
        }
        if (strcmp(operation, "UPG") == 0) {
            int planet_index, shield_index, upgrade_value;
            scanf("%d %d %d", &planet_index, &shield_index, &upgrade_value);
            upg(galaxy, planet_index, shield_index, upgrade_value);
        }
        if (strcmp(operation, "EXP") == 0) {
            int planet_index, shield_value;
            scanf("%d %d", &planet_index, &shield_value);
            exp_a(galaxy, planet_index, shield_value);
        }
        if (strcmp(operation, "RMV") == 0) {
            int planet_index, shield_index;
            scanf("%d %d", &planet_index, &shield_index);
            rmv(galaxy, planet_index, shield_index);
        }
        if (strcmp(operation, "COL") == 0) {
            int planet_index1, planet_index2;
            scanf("%d %d", &planet_index1, &planet_index2);
            col(galaxy, planet_index1, planet_index2);
        }
        if (strcmp(operation, "ROT") == 0) {
            int planet_index, units;
            char mode;
            scanf("%d %s %d", &planet_index, &mode, &units);
            rot(galaxy, planet_index, mode, units);
        }
        if (strcmp(operation, "SHW") == 0) {
            int planet_index;
            scanf("%d", &planet_index);
            shw(galaxy, planet_index);
        }
    }

    /* Se da free la galaxie */
    dll_node_t *current = galaxy->head;
    int galaxy_size = (int)dll_get_size(galaxy);
    for (int i = 0; i < galaxy_size; i++) {
        planet *removed_planet_data = (planet *)current->data;
        dll_free(&(removed_planet_data->shield));
        current = current->next;
    }  /* Se da free la scutul fiecarei planete */
    dll_free(&galaxy);

    return 0;
}
