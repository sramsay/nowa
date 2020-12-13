#ifndef PRODUCT_INCLUDED
#define PRODUCT_INCLUDED

#include <stdbool.h>

bool print_product(char station_id[restrict static 1], char* product_code);
bool print_product_json(char station_id[restrict static 1], char* product_code);

#endif
