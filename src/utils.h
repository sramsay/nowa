#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

#include <time.h>

double ftemp(double raw_temp);
double ctemp(double raw_temp);
char* dd_to_dms(const double coordinate);
char lat_dir(double latitude);
char lng_dir(double longitude);
int convert_iso8601(const char date_string[restrict static 1],
                    struct tm* date_data);

#endif
