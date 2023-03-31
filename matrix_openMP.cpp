#include <stdio.h>
#include <omp.h>

#define N 800
#define M 1000
#define P 1200

int main() {
    int i, j, k;
    double sum;
    double A[N][M], B[M][P], C[N][P];
    double start_time, end_time;

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

    // multiply matrices A and B
    start_time = omp_get_wtime();
    #pragma omp parallel for private(j,k,sum)
    for (i = 0; i < N; i++) {
        for (k = 0; k < P; k++) {
            sum = 0.0;
            for (j = 0; j < M; j++) {
                sum += A[i][j] * B[j][k];
            }
            C[i][k] = sum;
        }
    }
    end_time = omp_get_wtime();

    // print matrix C
    for (i = 0; i < N; i++) {
        for (k = 0; k < P; k++) {
            printf("%f ", C[i][k]);
        }
        printf("\n");
    }

    printf("Elapsed time = %f seconds\n", end_time - start_time);

    return 0;
}