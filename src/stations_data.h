#ifndef STATIONS_DATA_INCLUDED
#define STATIONS_DATA_INCLUDED

typedef struct station station;

struct station {
	char station_id[5];
	char name[50];
};

struct station* init_stations(char lat_long[restrict static 1]);

#endif
