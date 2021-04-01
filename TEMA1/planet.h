// Copyright 2021 Adrian-Valeriu Croitoru

#ifndef _HOME_STUDENT_DESKTOP_TEMA1_PLANET_H_
#define _HOME_STUDENT_DESKTOP_TEMA1_PLANET_H_

#define MSL 255  /* MAX_STRING_LENGTH */

typedef struct planet planet;
struct planet
{
    char name[MSL];
    int kills;
    doubly_linked_list_t *shield;
};

#endif  // _HOME_STUDENT_DESKTOP_TEMA1_PLANET_H_
