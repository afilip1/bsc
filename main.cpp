#include <algorithm>
#include <iostream>

#include "vec.hpp"

int main() {
    bsc::Vec<int> v{1, 2, 3, 4, 5};

    auto v2 = v.iter()
                  .filter([](int i) { return i % 2 != 0; })
                  .map<double>([](int i) { return 2.5 * i; })
                  .collect();

    for (auto v : v2) {
        std::cout << v << "\n";
    }

    std::cout << "End of iteration\n";
}
