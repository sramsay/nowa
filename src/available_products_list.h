#ifndef AVAILABLE_PRODUCTS_LIST_INCLUDED
#define AVAILABLE_PRODUCTS_LIST_INCLUDED

#include <stdbool.h>

bool print_available_products(char station_id[restrict static 1]);
bool print_available_products_json(char station_id[restrict static 1]);

#endif
