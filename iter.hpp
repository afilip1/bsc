#pragma once

#include <functional>
#include <optional>
#include <vector>

namespace bsc {
template <class T>
class Iterator;

template <class T>
class FilterIterator;

template <class T, class U>
class MapIterator;

template <class T>
class IterTrait {
   public:
    virtual std::optional<T> next() = 0;

    FilterIterator<T> filter(std::function<bool(T)> predicate) {
        return FilterIterator(*this, predicate);
    }

    template <class U>
    MapIterator<U, T> map(std::function<U(T)> transform) {
        return MapIterator(*this, transform);
    }

    std::vector<T> collect() {
        std::vector<T> ret;
        while (true) {
            auto maybe_next = next();
            if (!maybe_next) return ret;
            ret.push_back(*maybe_next);
        }
    }
};

template <class T>
class Iterator : public IterTrait<T> {
   public:
    Iterator(std::vector<T>& source)
        : source{source}, current{source.begin()} {}

    virtual std::optional<T> next() override {
        if (current == source.end()) {
            return {};
        }

        return *(current++);
    }

   private:
    std::vector<T>& source;
    typename std::vector<T>::iterator current;
};

template <class T>
class FilterIterator : public IterTrait<T> {
   public:
    FilterIterator(IterTrait<T>& parent, std::function<bool(T)> predicate)
        : parent(parent), predicate(predicate) {}

    virtual std::optional<T> next() override {
        while (true) {
            auto maybe_next = parent.next();
            if (!maybe_next) return {};
            if (predicate(*maybe_next)) return maybe_next;
        }
    }

   private:
    IterTrait<T>& parent;
    std::function<bool(T)> predicate;
};

template <class T, class U>
class MapIterator : public IterTrait<T> {
   public:
    MapIterator(IterTrait<U>& parent, std::function<T(U)> transform)
        : parent{parent}, transform{transform} {}

    virtual std::optional<T> next() override {
        auto maybe_next = parent.next();
        if (!maybe_next) return {};
        return transform(*maybe_next);
    }

   private:
    IterTrait<U>& parent;
    std::function<T(U)> transform;
};

}  // namespace bsc
