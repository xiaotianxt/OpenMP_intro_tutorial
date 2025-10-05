#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
    double A[10000];
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("%d\n", ID);
    }
    printf("All done\n");
}
