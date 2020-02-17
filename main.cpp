#include <algorithm>
#include <iostream>

#include "vec.hpp"

int main() {
    // bsc::Vec<int> vec{1, 2, 3, 4};

    // std::cout << vec.contains(1) << "\n";
    // std::cout << vec.contains(6) << "\n\n";

    // auto doubles = vec.filter([](int i) { return i > 1; }).map([](int i) {
    //     return i * 2;
    // });

    // for (int i : doubles) {
    //     std::cout << i << "\n";
    // }

    // auto sum = doubles.reduce(0, [](int acc, int i) { return acc + i; });
    // auto product = doubles.reduce(1, [](int acc, int i) { return acc * i; });

    // std::cout << sum << "\n" << product << "\n";

    bsc::Vec<int> vec{1, 2, 3, 4};
    auto iter = vec.iter();
    auto iter1 = iter.map<double>([](int i) { return 2.f * i; });
    auto iter2 = iter1.filter([](double e) { return e < 7.f; });

    while (iter2.has_next()) {
        std::cout << iter2.next() << "\n";
    }
}
