#ifndef ALERTS_DATA_INCLUDED
#define ALERTS_DATA_INCLUDED

#include <stdlib.h>

typedef struct alert alert;

struct alert {
	char* headline;
	char* description;
	char* instruction;
};

struct alert* init_alerts(char zone_id[restrict static 1]);

size_t alerts_count;

#endif
