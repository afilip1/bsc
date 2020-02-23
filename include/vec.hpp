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
    Vec(const std::vector<T>& other) : std::vector<T>{other} {}
    Vec(std::initializer_list<T> list) : std::vector<T>{list} {}

    bool contains(T elem) {
        return std::find(this->begin(), this->end(), elem) != this->end();
    }

    void append(Vec<T> other) {
        this->insert(this->end(), other.begin(), other.end());
    }

    VecAdapter<T> iter() { return VecAdapter<T>(*this); }
};

template <class TOut>
class VecAdapter : public IterTrait<TOut> {
   public:
    VecAdapter(std::vector<TOut>& source)
        : source{source}, current{source.begin()} {}

    virtual std::optional<TOut> next() override {
        if (current == source.end()) {
            return {};
        }

        return *(current++);
    }

   private:
    std::vector<TOut>& source;
    typename std::vector<TOut>::iterator current;
};

}  // namespace bsc
