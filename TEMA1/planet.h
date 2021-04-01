// Copyright 2021 Adrian-Valeriu Croitoru

#ifndef PLANET_H_
#define PLANET_H_

#define MSL 255  /* MAX_STRING_LENGTH */

typedef struct planet planet;
struct planet
{
    char name[MSL];
    int kills;
    doubly_linked_list_t *shield;
};

#endif  // PLANET_H_
