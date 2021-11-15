#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

sem_t *sem;

void *routine(void *num)
{
	sem_wait(sem); // semaphore lock
	for (int i = 0; i < 3; ++i)
	{
		printf("%d uses semaphore\n", *(int *)num);
		usleep(1000 * 1000);
	}
	sem_post(sem); // semaphore unlock
	return (num);
}

int main(void)
{
	int ret;
	pthread_t tid[4];
	int num[4];

	sem = sem_open("test_sem", O_CREAT | O_EXCL, 0644, 3); // value(counter) is 3
	if (sem == SEM_FAILED) // if failed to create semaphore 
	{
		fprintf(stderr, "sem errro\n");
		return (-1);
	}

	for (int i = 0; i < 4; ++i) // creating 3 thread
	{
		num[i] = i;
		pthread_create(&tid[i], NULL, routine, (void *)&num[i]);
	}
	for (int i = 0; i < 4; ++i)
		pthread_join(tid[i], NULL);

	ret = sem_close(sem); // close semaphore and release resources
	printf("sem_close: %d\n", ret);
	ret = sem_unlink("test_sem"); // unlink semaphore object
	printf("sem_unlink: %d\n", ret);

	return 0;
}