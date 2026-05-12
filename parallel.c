#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello(void);
double f(int i);

int main(int argc, char* argv[]) {
    int thread_count = strtol(argv[1], NULL, 10);
    int n = 100;
    double sum_static_10 = 0.0;
    double sum_static_1 = 0.0;

    #pragma omp parallel num_threads(thread_count)
    Hello();

    #pragma omp parallel for num_threads(thread_count) reduction(+:sum_static_10) schedule(static, 10)
    for (int i = 0; i <= n; i++) {
        sum_static_10 += f(i);
    }

    #pragma omp parallel for num_threads(thread_count) reduction(+:sum_static_1) schedule(static, 1)
    for (int i = 0; i <= n; i++) {
        sum_static_1 += f(i);
    }

    printf("Static chunk 10 sum = %.1f\n", sum_static_10);
    printf("Static chunk 1 sum = %.1f\n", sum_static_1);

    return 0;
}

void Hello(void) {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    printf("Hello from thread %d of %d\n", my_rank, thread_count);
}

double f(int i) {
    return i * 1.0;
}
