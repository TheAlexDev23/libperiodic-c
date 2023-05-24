#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>

#include "periodic.h"
#include "element.h"

char* periodic_source_location;

void periodic_set_database(char* location)
{
    periodic_source_location = location;
}

periodic_element_t** periodic_get_all_elements()
{
    periodic_element_t** elements = calloc(118, sizeof(periodic_element_t*));

    for (int i = 0; i < 118; i++)
    {
        elements[i] = periodic_get_element(i);
    }

    return elements;
}

periodic_element_t* periodic_get_element(int num)
{
    char* fm = periodic_source_location;
    FILE *fp = fopen(fm, "r");

    if (fp == NULL)
        return NULL;

    // Get the file size
    struct stat st;
    if (stat(fm, &st))
    {
        fclose(fp);
        return NULL;
    }

    int file_size = st.st_size;

    char *buffer = malloc(file_size + 1);
    buffer[file_size] = '\0';

    fread(buffer, file_size, 1, fp);
    fclose(fp);

    periodic_element_t* el = json_parse_element(num, buffer);

    free(buffer);
    return el;
}

void periodic_free_element(periodic_element_t* element)
{
    if (element == NULL)
    {
        return;
    }
    
    free(element->name);
    free(element->conf.conf);
    free(element);
}

void periodic_free_elements(periodic_element_t** elements)
{
    for (int i = 0; i < 118; i++)
    {
        periodic_free_element(elements[i]);
    }
}