#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>

using namespace std;

#define SIZE 10000
#define NUM_THREADS 6

vector<double> v(SIZE), w (SIZE), u(SIZE), p(SIZE), x(SIZE), y(SIZE);

void* calculate_vectors(void* args) {
    int thread_id = *(int*) args;
    int start = thread_id * (SIZE / NUM_THREADS);
    int end = (thread_id + 1) * (SIZE/NUM_THREADS);

    for (int i =start; i < end; i++) {
        u[i] = v[i] + w[i];
        p[i] = v[i] * w[i];
        x[i] = v[i] - w[i];
        y[i] = v[i] / (w[i] + 1e-6);
    }

    pthread_exit(nullptr);
}

int main() {
    srand(42);
    for(int i = 0; i <SIZE; i++){
        v[i] = rand() % 1000 / 10.0;
        w[i] = rand() % 1000 / 10.0;
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], nullptr, calculate_vectors, &thread_ids[i]);
    }

    for(int i = 0; i <NUM_THREADS; i++){
        pthread_join(threads[i], nullptr);
    }

    cout << "Sample Random Results: \n";
    for (int i = 0; i < 10; i++){
        std::cout << "v[" << i << "] = " << v[i]
                  << ", w[" << i << "] = " << w[i]
                  << ", u[" << i << "] = " << u[i]
                  << ", p[" << i << "] = " << p[i]
                  << ", x[" << i << "] = " << x[i]
                  << ", y[" << i << "] = " << y[i] << std::endl;
    }

    return 0;
}