#include <marsh/driver.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
            return driver_version();
        if (argv[1][0] == '-')
            return driver_help();
        if (argc != 2)
            return driver_help();
        return driver_lex_file(argv[1]);
    }

    return driver_help();
}
