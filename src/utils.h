#ifndef UTILS_INCLUDE
#define UTILS_INCLUDE

double ftemp(double raw_temp);
double ctemp(double raw_temp);

char* dd_to_dms(const double coordinate);
char lat_dir(double latitude);
char lng_dir(double longitude);

#endif
