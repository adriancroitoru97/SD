// Copyright 2021 ACS UPB

/**
 * Useful structures/macros
 *
 * https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die
 */

#ifndef _HOME_STUDENT_DESKTOP_TEMA1_UTILS_H_
#define _HOME_STUDENT_DESKTOP_TEMA1_UTILS_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)                                       \
    do {                                                                       \
        if (assertion) {                                                       \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
            perror(call_description);                                          \
            exit(errno);                                                       \
        }                                                                      \
    } while (0)

#endif  // _HOME_STUDENT_DESKTOP_TEMA1_UTILS_H_
