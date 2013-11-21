/*
 * bucketsort.hpp
 *
 *  Created on: 2013-11-21
 *      Author: Rong Xiao
 */

#ifndef BUCKETSORT_HPP_
#define BUCKETSORT_HPP_
#include <vector>

namespace sortutils {
using std::vector;
typedef vector<int>::size_type size_t;

template <class T> class KeyOrder {
    size_t size;
    typedef size_t (*OrderFunctionPointer)(const T& );
    OrderFunctionPointer orderf;
public:
    KeyOrder(OrderFunctionPointer f, size_t s) : orderf(f), size(s) {
        if (size == 0) {
            throw "KeyOrder must have non-zero size";
        }
    }
    size_t getSize() const {
        return size;
    }
    size_t operator()(const T& val) const {
        return orderf(val);
    }
};

template <class RandomIterator, class T=typename RandomIterator::value_type, class OrderFunc= KeyOrder<T> > void bucketsort(RandomIterator start, RandomIterator last, const OrderFunc& f) {
    if (start>=last) {
        return;
    }
    size_t size = f.getSize();
    size_t *indices_offset = new size_t[size];

    for (size_t i = 0; i<size; ++i) {
        indices_offset[i] = 0;
    }

    for (RandomIterator it = start; it != last; ++it ) {
        ++indices_offset[f(*it)];
    }

    size_t *unsorted = new size_t[size];

    unsorted[0] = indices_offset[0];
    for (size_t i = 1; i<size; ++i) {
        unsorted[i] = indices_offset[i];
        indices_offset[i] += indices_offset[i-1];
    }

    size_t current_sorting = size;
    while (current_sorting>0) {
        if (unsorted[current_sorting-1] == 0) {
            --current_sorting;
        } else {
            RandomIterator cursor = start+(--indices_offset[current_sorting-1]);
            T& val = *cursor;
            size_t key_order = f(val);
            while (key_order +1 != current_sorting) {
                RandomIterator final_place = start+(--indices_offset[key_order]);
                // Optimization: using move based swap here
                T tmp = *final_place;
                *final_place = val;
                val = tmp;
                --unsorted[key_order];
                key_order = f(val);
            }
            --unsorted[key_order];
        }
    }
    delete [] unsorted;
    delete [] indices_offset;
}

}



#endif /* BUCKETSORT_HPP_ */
