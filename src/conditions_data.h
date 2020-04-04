#ifndef CONDITIONS_DATA_INCLUDED
#define CONDITIONS_DATA_INCLUDED

typedef struct current_conditions current_conditions;

struct current_conditions {
  char summary[50];
  double temperature;
  double dewpoint;
  int wind_direction;
  double wind_speed;
};

current_conditions* init_conditions(char station_id[restrict static 1]);

#endif
