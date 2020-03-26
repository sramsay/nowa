#ifndef CONDITIONS_INCLUDED
#define CONDITIONS_INCLUDED

typedef struct currentConditions currentConditions;
struct currentConditions {
  char summary[50];
  double temperature;
  double dewpoint;
  int wind_direction;
  double wind_speed;
};

void init_conditions(char url[restrict static 1]);
void print_conditions();

#endif
