#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define N 800
#define M 1000
#define P 1200
#define NUM_THREADS 4

double A[N][M], B[M][P], C[N][P];
pthread_t threads[NUM_THREADS];
int thread_args[NUM_THREADS];

void *matrix_multiply(void *arg) {
    int tid = *((int *) arg);
    int i, j, k;
    double sum;

    for (i = tid; i < N; i += NUM_THREADS) {
        for (k = 0; k < P; k++) {
            sum = 0.0;
            for (j = 0; j < M; j++) {
                sum += A[i][j] * B[j][k];
            }
            C[i][k] = sum;
        }
    }

    pthread_exit(NULL);
}

int main() {
    int i, j, k;
    struct timeval start_time, end_time;
    double elapsed_time;

    // initialize matrices A and B
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            A[i][j] = i + j;
        }
    }
    for (j = 0; j < M; j++) {
        for (k = 0; k < P; k++) {
            B[j][k] = j + k;
        }
    }

    // create threads
    gettimeofday(&start_time, NULL);
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, matrix_multiply, &thread_args[i]);
    }

    // join threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end_time, NULL);

    // print matrix C
    for (i = 0; i < N; i++) {
        for (k = 0; k < P; k++) {
            printf("%f ", C[i][k]);
        }
        printf("\n");
    }

    elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Elapsed time = %f seconds\n", elapsed_time);

    return 0;
}