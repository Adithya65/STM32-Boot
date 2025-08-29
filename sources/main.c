#include "stm_blinky.h"
#include "freertos_tests.h"
#include <stdint.h>


#define CLI          1
#define SAMPLES      2
#define TESTS        3

void cli_task();
void stm_samples();

int main()
{
#if APP_MODE == CLI
    cli_task();
#elif APP_MODE == SAMPLES
    stm_samples();
#elif APP_MODE == TESTS
    (void)freertos_tests();
#else
#error "Invalid Source"
#endif

    while(1)
        ;
}
