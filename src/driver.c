#include <stdio.h>
#include "marsh/driver.h"

#define VERSION "0.1"

int driver_help(){
    printf("-v, --version   prints compiler version\n");
    return 0;
}

int driver_version(){
    printf("%s\n", VERSION);
    return 0;
}
