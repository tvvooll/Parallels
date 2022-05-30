#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <omp.h>

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

int main(int argc, const char* argv[]) {
    omp_set_num_threads(4);

    num volume;
    std::cin >> volume;

    num* array = get_array(volume);
    num result = 0;


    auto before = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (num i = 0; i < volume; ++i) {
        if (number_starts_with(array[i], 1)) {
            result++;
        }
    }
    auto after = std::chrono::high_resolution_clock::now();

    std::cout << "Number of matches: " << result << std::endl;
    std::cout << "Seconds elapsed: " << std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count() / 1000000000.0 << "s" << std::endl;

    return 0;
}