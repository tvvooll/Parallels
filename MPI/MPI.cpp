#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include <cmath>
#include <string>

typedef unsigned long long num;

bool number_starts_with(num number, int start)
{
    auto a = std::hash<num>()(number);
    while (a / 10 != 0)
        a = a / 10;

    return a == start;
}

num* get_array(num size)
{
    num* array = new num[size];
    for (num i = 0; i < size; i++)
        std::cin >> array[i];
    return array;
}

int main(int argc, char** argv) {

    int rank, n;
    num volume, count, total;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    num* tasks_distribution = new num[n];

    num* array = new num[1];

    if (rank == 0) {
        std::cin >> volume;
        array = get_array(volume);

        for (int i = 0; i < n; ++i) {
            tasks_distribution[i] = volume / n;
        }
    }

    MPI_Bcast(&volume, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    if (rank != 0) {
        array = new num[volume];
    }

    MPI_Bcast(array, volume, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Scatter(tasks_distribution, 1, MPI_UNSIGNED_LONG_LONG, &count,
                                    1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

    double before = MPI_Wtime();
    num result = 0;
    
    for (num i = 0; i < (rank == n - 1? count + volume % n: count); ++i) {
        if (number_starts_with(array[rank * count + i], 1)) {
            result++;
        }
    }
    
    MPI_Reduce(&result, &total, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    double after = MPI_Wtime();

    if (rank == 0) {
        std::cout << "Number of matches: " << total << std::endl;
        std::cout << "Seconds elapsed: " << (after - before) << "s" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
