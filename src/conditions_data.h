#ifndef CONDITIONS_DATA_INCLUDED
#define CONDITIONS_DATA_INCLUDED

typedef struct currentConditions currentConditions;

struct currentConditions {
  char summary[50];
  double temperature;
  double dewpoint;
  int wind_direction;
  double wind_speed;
};

currentConditions* init_conditions(char station_id[restrict static 1]);

#endif
