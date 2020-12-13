#ifndef AVAILABLE_PRODUCTS_LIST_DATA_INCLUDED
#define AVAILABLE_PRODUCTS_LIST_DATA_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

typedef struct product product;

struct product {
  char* product_code;
  char* product_name;
};

struct product* init_available_products(char station_id[restrict static 1]);

bool construct_available_product_list_url(char station_id[restrict static 1],
                                           char* available_product_list_url[]);

extern size_t product_count;

#endif
