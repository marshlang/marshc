#include "driver.h"
#include <string.h>
int main(int argc, char** argv){
    if(argc <= 1)
        driver_help();

    if(strcmp(argv[1], "-v") || strcmp(argv[1], "--version"))
        driver_version();
    return 0;
}
