#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "bsc.hpp"
#include "iter.hpp"

namespace bsc {
template <class T>
class Vec : public std::vector<T> {
   public:
    Vec() = default;
    Vec(const Vec&) = default;
    Vec(const std::vector<T>& other) : std::vector<T>(other) {}
    Vec(std::initializer_list<T> list) : std::vector<T>(list) {}

    bool contains(T elem) {
        return std::find(this->begin(), this->end(), elem) != this->end();
    }

    Iterator<T> iter() { return Iterator<T>(*this); }
};

}  // namespace bsc