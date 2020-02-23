#pragma once

#include <unordered_map>

#include "bsc.hpp"
#include "iter.hpp"

namespace bsc {

template <class K, class V>
class Map : public std::unordered_map<K, V> {
   public:
    Map() = default;

    MapAdapter<K, V> iter() { return MapAdapter<K, V>(*this); }
};

template <class K, class V>
class MapAdapter : public IterTrait<std::pair<K, V>> {
   public:
    MapAdapter(std::unordered_map<K, V>& source)
        : source{source}, current{source.begin()} {}

    virtual std::optional<std::pair<K, V>> next() override {
        if (current == source.end()) {
            return {};
        }

        return *(current++);
    }

   private:
    std::unordered_map<K, V>& source;
    typename std::unordered_map<K, V>::iterator current;
};

}  // namespace bsc
