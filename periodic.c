#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>>

#include "periodic.h"
#include "element.h"

periodic_element_t* periodic_get_element(int num)
{
    FILE *fp = fopen("Periodic-Table-JSON/PeriodicTableJSON.json", "r");
    // Get the file size
    struct stat st;
    if (stat("Periodic-Table-JSON/PeriodicTableJSON.json", &st))
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

void free_periodic_element(periodic_element_t* element)
{
    free(element->name);
    free(element->conf.conf);
    free(element);
}