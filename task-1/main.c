#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg)
{
    printf("In child thread\n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_func, NULL);
    
    printf("In main thread\n");

    pthread_join(thread_id, NULL);
    return 0;
}
