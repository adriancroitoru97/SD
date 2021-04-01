// Copyright 2021 Adrian-Valeriu Croitoru

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

void
add(doubly_linked_list_t *galaxy, char name[], int index, int shields);

void
blh(doubly_linked_list_t *galaxy, int index, int mode);

void
upg(doubly_linked_list_t *galaxy, int index, int shield, int value);

void
exp_a(doubly_linked_list_t *galaxy, int index, int shield_value);

void
rmv(doubly_linked_list_t *galaxy, int planet_index, int shield_index);

void
col(doubly_linked_list_t *galaxy, int index1, int index2);

void
rot(doubly_linked_list_t *galaxy, int index, char mode, int units);

void
shw(doubly_linked_list_t *galaxy, int index);

#endif  // OPERATIONS_H_
