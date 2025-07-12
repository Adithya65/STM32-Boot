#ifndef __FREERTOS_TESTS__
#define __FREERTOS_TESTS__

#define TEST_ASSERT(cond, msg)                            \
    do {                                                  \
        if (!(cond)) {                                    \
            for (;;) ;                                    \
        }                                                 \
    } while (0)

#define TEST_LOG(msg)           printf("Test passed: %s\n", msg)


#define SEMAPHORE_TEST          1
#define QUEUE_TEST              0
#define MUTEX_TEST              0

void freertos_tests();

int semaphore_tests();
int mutex_tests();
int queue_tests();

#endif
