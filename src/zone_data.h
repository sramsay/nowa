#ifndef ALERTS_INCLUDED
#define ALERTS_INCLUDED

typedef struct alerts alerts

struct alerts {
	char* headline;
	char* description;
	char* instruction;
};

struct alerts* init_alerts(char zone_id[restrict static 1], struct alerts* alert);

#endif
