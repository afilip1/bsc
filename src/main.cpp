#include <iostream>

#include "vec.hpp"

int main() {
    bsc::Vec<int> v{1, 2, 3, 4, 5};

    v.iter()
        .filter([](int i) { return i % 2 != 0; })
        .map<double>([](int i) { return 2.5 * i; })
        .for_each([](auto x) { std::cout << x << "\n"; });
}
