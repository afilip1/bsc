#pragma once

#include <cstdint>
#include <string>

#include "bsc.hpp"
#include "vec.hpp"

namespace bsc {

class StringAdapter : public IterTrait<char> {
   public:
    StringAdapter(std::string& source)
        : source{source}, current{source.begin()} {}

    virtual std::optional<char> next() override {
        if (current == source.end()) {
            return {};
        }

        return *(current++);
    }

   private:
    std::string& source;
    typename std::string::iterator current;
};

class String : public std::string {
   public:
    String() = default;
    String(const std::string& other) : std::string{other} {}

    Vec<String> split_on(char delim) {
        Vec<String> parts;

        auto iter = this->iter();

        String acc;
        while (true) {
            auto maybe_char = iter.next();
            if (!maybe_char) {
                parts.push_back(acc);
                return parts;
            } else if (*maybe_char == delim) {
                parts.push_back(acc);
                acc = String();
            } else {
                acc += *maybe_char;
            }
        }
    }

    StringAdapter iter() { return StringAdapter(*this); }
};

template <>
template <>
inline String IterTrait<String>::join(char delim) {
    String joined;
    auto maybe_next = this->next();
    if (!maybe_next) return joined;
    joined += *maybe_next;

    while (true) {
        auto maybe_next = this->next();
        if (!maybe_next) return joined;
        joined += delim + *maybe_next;
    }
}

}  // namespace bsc
