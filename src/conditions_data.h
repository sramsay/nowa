#ifndef CONDITIONS_DATA_INCLUDED
#define CONDITIONS_DATA_INCLUDED

#include <stdbool.h>

typedef struct current_conditions current_conditions;

struct current_conditions {
  char* summary;
  double temperature;
  double dewpoint;
  int wind_direction;
  double wind_speed;
};

bool init_conditions(char station_id[restrict static 1],
                     struct current_conditions* current);
bool construct_conditions_url(char station_id[restrict static 1], char* conditions_url[static 1]);
void cleanup_conditions(struct current_conditions* current);
 
#endif
