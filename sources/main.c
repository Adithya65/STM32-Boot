#include "stm_blinky.h"

#define RUN_FREERTOS_TESTS   0
#define RUN_STM_SAMPLE       1

int main()
{
#if RUN_STM_SAMPLE
    stm_blinky_app();
#elif RUN_FREERTOS_TESTS
    freertos_tests();
#else
#error "Invalid Source"
#endif

    while(1);
}
