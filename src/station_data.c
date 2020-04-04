#include "station_data.h"

#include <stdio.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

station_info* init_station(char station_id[restrict static 1]) {
  char* url = malloc(40);
  sprintf(url, "%s%s", "https://api.weather.gov/stations/", station_id);
  cJSON* station_json = json_init(url);

  cJSON* geometry_json =
      cJSON_GetObjectItemCaseSensitive(station_json, "geometry");
  cJSON* coordinates_json =
      cJSON_GetObjectItemCaseSensitive(geometry_json, "coordinates");

  cJSON* longitude_json = cJSON_GetArrayItem(coordinates_json, 0);
  cJSON* latitude_json = cJSON_GetArrayItem(coordinates_json, 1);

  station_info* info = malloc(sizeof(station_info));
  info->latitude = latitude_json->valuedouble;
  info->longitude = longitude_json->valuedouble;

  cJSON* properties_json =
      cJSON_GetObjectItemCaseSensitive(station_json, "properties");
  cJSON* elevation_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "elevation");
  cJSON* elevation_value_json =
      cJSON_GetObjectItemCaseSensitive(elevation_json, "value");

  info->elevation = elevation_value_json->valuedouble;

  cJSON* name_json = cJSON_GetObjectItemCaseSensitive(properties_json, "name");

  strcpy(info->name, name_json->valuestring);

  free(url);
  cJSON_Delete(station_json);

  return info;
}
