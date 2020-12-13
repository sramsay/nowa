#ifndef PRODUCT_DATA_INCLUDED
#define PRODUCT_DATA_INCLUDED

#include <stdbool.h>

typedef struct product product;

struct product {
  char* product_name;
  char* product_text;
};

bool init_product(char station_id[restrict static 1], struct product* pd,
                  char* product_code);
bool construct_product_list_url(char station_id[restrict static 1],
                                char* product_url[], char* product_code);
void cleanup_product(struct product* pd);

#endif
