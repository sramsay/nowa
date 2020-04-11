#ifndef ZONEINFO_DATA_INCLUDED
#define ZONEINFO_DATA_INCLUDED

#include <stdbool.h>

typedef struct zoneinfo zoneinfo;

struct zoneinfo {
	char id[7];
	char name[50];
	char state[3];
};

bool init_zoneinfo(char station_id[restrict static 1], struct zoneinfo* zone);

#endif
