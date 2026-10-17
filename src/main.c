#include <marsh/driver.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
            return driver_version();
        return driver_help();
    }

    return driver_lex_example();
}
