#include <json-c/json.h>
#include <string.h>

#include "element.h"

char* json_obj_to_string(json_object* obj)
{
    char* json_string = (char*)json_object_get_string(obj);
    char* string = malloc(strlen(json_string) + 1);
    strcpy(string, json_string);

    return string;
}

periodic_element_t* json_parse_element(int number, char* buffer)
{
    json_object* parent = json_tokener_parse(buffer);
    json_object* elements;
    json_object_object_get_ex(parent, "elements", &elements);

    json_object* element = json_object_array_get_idx(elements, number);

    if (element == NULL)
        return NULL;

    periodic_element_t* periodic_element = malloc(sizeof(periodic_element_t));

    if (periodic_element == NULL)
        return NULL;

    json_object* name;
    json_object* symbol;

    json_object* group;
    json_object* period;

    json_object* posx;
    json_object* posy;

    json_object* shells;
    json_object* electron_configuration;

    json_object_object_get_ex(element, "name", &name);
    json_object_object_get_ex(element, "symbol", &symbol);
    json_object_object_get_ex(element, "group", &group);
    json_object_object_get_ex(element, "xpos", &posx);
    json_object_object_get_ex(element, "ypos", &posy);
    json_object_object_get_ex(element, "shells", &shells);
    json_object_object_get_ex(element, "electron_configuration", &electron_configuration);

    periodic_element->name = json_obj_to_string(name);
    periodic_element->symbol = json_obj_to_string(symbol);
    periodic_element->group = json_object_get_int(group);
    periodic_element->period = json_object_get_int(period);

    periodic_element->pos.posX = json_object_get_int(posx) - 1;
    periodic_element->pos.posY = json_object_get_int(posy) - 1;

    periodic_element->number = number + 1;

    size_t shell_length = json_object_array_length(shells);
    periodic_element->conf.shells_amnt = (int)shell_length;
    for (size_t i = 0; i < shell_length; i++)
    {
        json_object* element = json_object_array_get_idx(shells, i);
        periodic_element->conf.shells[i] = json_object_get_int(element);
    }

    periodic_element->conf.conf = json_obj_to_string(electron_configuration);

    return periodic_element;
}
