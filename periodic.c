#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>

#include "periodic.h"
#include "element.h"

periodic_element_t** periodic_get_all_elements()
{
    periodic_element_t* elements[128];

    for (int i = 0; i < 128; i++)
    {
        elements[i] = periodic_get_element(i);
    }

    return elements;
}

periodic_element_t* periodic_get_element(int num)
{
    char* fm = "Periodic-Table-JSON/PeriodicTableJSON.json";
    FILE *fp = fopen(fm, "r");

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
    free(element->name);
    free(element->conf.conf);
    free(element);
}

void periodic_free_elements(periodic_element_t** elements)
{
    for (int i = 0; i < elements; i++)
    {
        periodic_free_element(elements[i]);
    }
}