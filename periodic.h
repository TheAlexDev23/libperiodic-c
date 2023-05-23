#ifndef _PERIODIC_H_INCLUDED
#define _PERIODIC_H_INCLUDED

typedef struct _periodic_element_pos {
    int posX;
    int posY;
} periodic_element_pos_t;

typedef struct _periodic_element_conf {
    /* Length of shells */
    int shells_amnt;
    /* Number of electrons in each shell */
    int shells[8];
    /* Strign representing electronic configuration */
    char* conf;
} periodic_element_conf_t;

typedef struct _periodic_element {
    char* name;
    int number;

    int group;
    int period;
    periodic_element_pos_t pos;

    periodic_element_conf_t conf;
} periodic_element_t;

/* Returns array of all elements */
periodic_element_t** periodic_get_all_elements();

/* Returns single element num */
periodic_element_t* periodic_get_element(int num);

/* Frees a periodic_element_t allocated by periodic_get_element */
void periodic_free_element(periodic_element_t* element);
/* Frees array of elements alloacted by periodic_get_all_elements */
void periodic_free_elements(periodic_element_t** elements);

#endif