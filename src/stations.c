#include "stations.h"

#include <pcre.h>

void print_stations(char lat_long[static 1]) {

	pcre* regex = { 0 };
	const char* pcreErrorStr = (void *)0;
	int pcreErrorOffset = 0;

	char* regexString = "(-?[0-9]*\\.[0-9]+),(-?[0-9]*\\.[0-9]+)";

	regex = pcre_compile(regexString, 0, &pcreErrorStr, &pcreErrorOffset, NULL);

	pcre_free(regex);

}
