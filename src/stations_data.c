#include "stations_data.h"

#include <assert.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "third_party/cJSON.h"

static char* construct_points_url(char lat_long[restrict static 1]);

struct station* init_stations(char lat_long[restrict static 1]) {
  char* points_url = construct_points_url(lat_long);
  cJSON* points_json = json_init(points_url);

  cJSON* points_properties_json =
      cJSON_GetObjectItemCaseSensitive(points_json, "properties");
  cJSON* observation_stations_json = cJSON_GetObjectItemCaseSensitive(
      points_properties_json, "observationStations");

  char* station_url = observation_stations_json->valuestring;

  cJSON* stations_json = json_init(station_url);

  cJSON* features_json =
      cJSON_GetObjectItemCaseSensitive(stations_json, "features");

  station_count = cJSON_GetArraySize(features_json);
  struct station* station_list = malloc(sizeof(struct station) * station_count);

  const cJSON* feature_json = {0};
  int count = 0;
  cJSON_ArrayForEach(feature_json, features_json) {
    cJSON* station_properties_json =
        cJSON_GetObjectItemCaseSensitive(feature_json, "properties");

    cJSON* station_identifier_json = cJSON_GetObjectItemCaseSensitive(
        station_properties_json, "stationIdentifier");
    cJSON* name_json =
        cJSON_GetObjectItemCaseSensitive(station_properties_json, "name");

    strcpy(station_list[count].station_id,
           station_identifier_json->valuestring);
    strcpy(station_list[count].name, name_json->valuestring);
    count++;
  }

  cJSON_Delete(points_json);
  cJSON_Delete(stations_json);

  return station_list;
}

static char* construct_points_url(char lat_long[restrict static 1]) {
  // Matches lat/longs of the general form 39.809734,-98.555620
  char* regex_str = "(-?[0-9]*\\.[0-9]+),(-?[0-9]*\\.[0-9]+)";

  const char* pcre_error_msg = {0};
  int pcre_error_offset = {0};
  pcre* regex =
      pcre_compile(regex_str, 0, &pcre_error_msg, &pcre_error_offset, NULL);

  if (regex == NULL) {
    printf("Error: Could not compile '%s': %s\n", regex_str, pcre_error_msg);
    exit(1);
  }

  // Optimize the regex
  pcre_extra* extra = pcre_study(regex, 0, &pcre_error_msg);

  if (pcre_error_msg != NULL) {
    printf("ERROR: Could not study '%s': %s\n", regex_str, pcre_error_msg);
    exit(1);
  }

  // NWS will only accept four digits of precision (which is plenty), and
  // insists on truncated trailing zeros.  So this magic number is really just
  // based on something like -98.5556
  int sub_str[10] = {0};
  int pcre_exec_ret =
      pcre_exec(regex, extra, lat_long, strlen(lat_long), 0, 0, sub_str, 50);

  const char* latitude_match = {0};
  const char* longitude_match = {0};
  pcre_get_substring(lat_long, sub_str, pcre_exec_ret, 1, &(latitude_match));
  pcre_get_substring(lat_long, sub_str, pcre_exec_ret, 2, &(longitude_match));
  char* end = {0};
  assert(strlen(latitude_match) <= 10);
  assert(strlen(longitude_match) <= 10);
  // Converting these strings to actual doubles so we can set precision and
  // truncate zeros
  double latitude = strtod(latitude_match, &end);
  double longitude = strtod(longitude_match, &end);

  char* url = malloc(50);
  sprintf(url, "%s%.4g,%.4g", "https://api.weather.gov/points/", latitude,
          longitude);

  pcre_free_substring(latitude_match);
  pcre_free_substring(longitude_match);
  pcre_free(regex);

  if (extra != NULL) {
#ifdef PCRE_CONFIG_JIT
    pcre_free_study(extra);
#else
    pcre_free(extra);
#endif
  }
  return url;
}
