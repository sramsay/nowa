#include "station_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

bool init_station(char station_id[restrict static 1],
                  struct station_info* info) {
  char* station_url = malloc(40);
  sprintf(station_url, "%s%s", "https://api.weather.gov/stations/", station_id);
  cJSON* station_json = json_init(station_url);

  cJSON* geometry_json =
      cJSON_GetObjectItemCaseSensitive(station_json, "geometry");
  cJSON* coordinates_json =
      cJSON_GetObjectItemCaseSensitive(geometry_json, "coordinates");

  cJSON* longitude_json = cJSON_GetArrayItem(coordinates_json, 0);
  cJSON* latitude_json = cJSON_GetArrayItem(coordinates_json, 1);
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

  cJSON* timezone_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "timeZone");
  strcpy(info->timezone, timezone_json->valuestring);

  cJSON* forecast_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "forecast");
  strcpy(info->forecast_url, forecast_json->valuestring);

  cJSON* county_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "county");
  strcpy(info->county_url, county_json->valuestring);

  cJSON* fire_weather_zone_json =
      cJSON_GetObjectItemCaseSensitive(properties_json, "fireWeatherZone");
  strcpy(info->fire_weather_zone_url, fire_weather_zone_json->valuestring);

  free(station_url);
  cJSON_Delete(station_json);

  return true;
}
