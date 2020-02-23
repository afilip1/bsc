#pragma once

#include <functional>
#include <optional>
#include <vector>

#include "bsc.hpp"
#include "vec.hpp"

namespace bsc {

template <class TOut>
class IterTrait {
   public:
    virtual std::optional<TOut> next() = 0;

    FilterIterator<TOut> filter(std::function<bool(TOut)> predicate) {
        return FilterIterator(*this, predicate);
    }

    template <class TTransformed>
    MapIterator<TTransformed, TOut> map(
        std::function<TTransformed(TOut)> transform) {
        return MapIterator(*this, transform);
    }

    Vec<TOut> collect() {
        Vec<TOut> ret;
        while (true) {
            auto maybe_next = next();
            if (!maybe_next) return ret;
            ret.push_back(*maybe_next);
        }
    }

    void for_each(std::function<void(TOut)> action) {
        while (true) {
            auto maybe_next = next();
            if (!maybe_next) return;
            action(*maybe_next);
        }
    }
};

template <class TOut>
class FilterIterator : public IterTrait<TOut> {
   public:
    FilterIterator(IterTrait<TOut>& parent, std::function<bool(TOut)> predicate)
        : parent(parent), predicate(predicate) {}

    virtual std::optional<TOut> next() override {
        while (true) {
            auto maybe_next = parent.next();
            if (!maybe_next) return {};
            if (predicate(*maybe_next)) return maybe_next;
        }
    }

   private:
    IterTrait<TOut>& parent;
    std::function<bool(TOut)> predicate;
};

template <class TOut, class TIn>
class MapIterator : public IterTrait<TOut> {
   public:
    MapIterator(IterTrait<TIn>& parent, std::function<TOut(TIn)> transform)
        : parent{parent}, transform{transform} {}

    virtual std::optional<TOut> next() override {
        auto maybe_next = parent.next();
        if (!maybe_next) return {};
        return transform(*maybe_next);
    }

   private:
    IterTrait<TIn>& parent;
    std::function<TOut(TIn)> transform;
};

}  // namespace bsc
