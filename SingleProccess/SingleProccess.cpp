#include <iostream>
#include <functional>
#include <chrono>

long long* get_array(long long);
bool number_starts_with(long long, int);

int main()
{
    long long n;
    long long result = 0;
    std::cin >> n;

    auto array = get_array(n);

    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        if (number_starts_with(array[i], 1))
            result++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    std::cout << "Time spent: " << duration / 1000000000.0 << " seconds" << std::endl;
    std::cout << "Checked true: " << result;
    std::cin.get();
    delete[] array;

    return 0; 
}

bool number_starts_with(long long number, int start)
{
    auto a = std::hash<long long>()(number);
    while (a / 10 != 0)
        a = a / 10;

    return a == start;
}

long long* get_array(long long size)
{
    long long* array = new long long[size];
    for (long long i = 0; i < size; i++)
        std::cin >> array[i];
    return array;
}