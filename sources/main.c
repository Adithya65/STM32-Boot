#include "stm_blinky.h"
#include "freertos_tests.h"

#define RUN_FREERTOS_TESTS   1
#define RUN_STM_SAMPLE       0

int main()
{
#if RUN_STM_SAMPLE
    stm_blinky_app();
#elif RUN_FREERTOS_TESTS
    (void)freertos_tests();
#else
#error "Invalid Source"
#endif

    while(1);
}
