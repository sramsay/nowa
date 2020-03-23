#include <stdio.h>

#include <config.h> 

void print_version() {
  printf("%s %s\n", PACKAGE, PACKAGE_VERSION);
  printf("Copyright © %s by Stephen Ramsay\n", COPYRIGHT_DATES);
  printf(
      "License GPVv3+: GNU GPL version 3 or later "
      "<https://gnu.org/licenses.gpl.html>.\n");
  printf(
      "This is free software: you are free to change and redistribute it.\n");
  printf("There is NO WARRANTY, to the extent permitted by law.\n");
}
