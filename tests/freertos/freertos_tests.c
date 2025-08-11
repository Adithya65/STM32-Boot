#include "freertos_tests.h"

void freertos_tests()
{
#if SEMAPHORE_TEST
    semaphore_tests();
#elif QUEUE_TEST
    queue_tests();
#elif MUTEX_TEST
    mutex_tests();
#elif NUM_TEST
    number_tests();
#else
#error invalid selection
#endif 
}

