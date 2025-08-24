#include "stm_blinky.h"
#include "freertos_tests.h"
#include <stdint.h>

#define RUN_FREERTOS_TESTS   0
#define RUN_STM_SAMPLE       1
#define RUN_CLI_TASK         0

void cli_task();
void stm_samples();

int main()
{
#if RUN_STM_SAMPLE
    stm_samples();
#elif RUN_FREERTOS_TESTS
    (void)freertos_tests();
#elif RUN_CLI_TASK
    cli_task();
#else
#error "Invalid Source"
#endif

    while(1);
}
