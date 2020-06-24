#ifndef AIR_QUALITY_DATA_INCLUDED
#define AIR_QUALITY_DATA_INCLUDED

#include <stdbool.h>

typedef struct air_quality air_quality;

struct air_quality {
  char* product_name;
	char* product_text;
};

bool init_air_quality(char station_id[restrict static 1],
                     struct air_quality* aqi);
bool construct_air_quality_list_url(char station_id[restrict static 1],
                              char* air_quality_url[]);
void cleanup_air_quality(struct air_quality* air_quality);

#endif
