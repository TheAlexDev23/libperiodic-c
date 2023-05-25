# Periodic C

A library that stores and has an API for accessing information about elements of the periodic table.

Part of a series of projects I made for a school project. But it still can be used on it's own.

# API

Configuring the library. Should be called before calling any other API function.

```C
#include <libperiodic-c/periodic.h>

...
periodic_set_database("Path of Periodic-Table-JSON/PeriodicTableJSON.json");
...
```

Getting single element by number

```C
#include <libperiodic-c/periodic.h>

int main()
{
    ...
    periodic_element_t* element = periodic_get_element(my_num);
    ...
    periodic_free_element(element);
    ...
}
```

Getting all elements

```C
#include <libperiodic-c/periodic.h>

int main()
{
    ...
    periodic_element_t** elements = periodic_get_all_elements();
    ...
    periodic_free_elements(elements);
    ...
}
```