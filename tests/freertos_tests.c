#include "freertos_tests.h"

void freertos_tests()
{
#if SEMAPHORE_TEST
    semaphore_tests();
#elif QUEUE_TEST
    queue_tests();
#elif MUTEX_TEST
    mutext_tests();
#endif 
}

