#include <algorithm>
#include <functional>
#include <vector>

namespace bsc {

template <class E>
class Iterator;

template <class E, class O>
class MapIterator;

template <class E>
class FilterIterator;

template <class E>
class Vec : public std::vector<E> {
   public:
    Vec() = default;
    Vec(const Vec&) = default;
    Vec(std::initializer_list<E> list) : std::vector<E>(list) {}

    bool contains(E elem) {
        return std::find(this->begin(), this->end(), elem) != this->end();
    }

    template <class A>
    Vec map(A action) {
        Vec mapped;
        for (E elem : *this) {
            mapped.push_back(action(elem));
        }
        return mapped;
    }

    template <class P>
    Vec filter(P predicate) {
        Vec filtered;
        std::copy_if(this->begin(), this->end(), std::back_inserter(filtered),
                     predicate);
        return filtered;
    }

    template <class A, class F>
    A reduce(A accumulator, F function) {
        for (E elem : *this) {
            accumulator = function(accumulator, elem);
        }
        return accumulator;
    }

    Iterator<E> iter() { return Iterator<E>(*this); }
};

template <class E>
class Iterator {
   public:
    Iterator() = default;
    Iterator(Vec<E>& source) {
        _current = source.begin();
        _end = source.end();
    }

    virtual bool has_next() { return _current != _end; }
    virtual E next() { return *(_current++); }

    auto begin() { return _current; }
    auto end() { return _end; }

    template <class O>
    auto map(std::function<O(E)> function) {
        return MapIterator<E, O>(*this, function);
    }

   private:
    typename Vec<E>::iterator _current;
    typename Vec<E>::iterator _end;
};

template <class E, class O>
class MapIterator : public Iterator<E> {
   public:
    MapIterator(Iterator<E>& iter, std::function<O(E)> function)
        : _parent{iter}, _function{function} {}

    virtual bool has_next() override { return _parent.has_next(); }
    virtual O next() { return _function(_parent.next()); }

    auto filter(std::function<bool(E)> predicate) {
        return FilterIterator<E>(*this, predicate);
    }

   private:
    Iterator<E>& _parent;
    std::function<O(E)> _function;
};

template <class E>
class FilterIterator {
   public:
    FilterIterator(Iterator<E>& parent, std::function<bool(E)> predicate)
        : _parent{parent}, _predicate{predicate} {}

    bool has_next() { return _parent.has_next(); }
    E next() { return _parent.next(); }

   private:
    Iterator<E>& _parent;
    std::function<bool(E)> _predicate;
};

}  // namespace bsc
