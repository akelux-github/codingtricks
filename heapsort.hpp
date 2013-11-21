/*
 * heapsort.hpp
 *
 *  Created on: 2013-11-21
 *      Author: Rong Xiao
 */

#ifndef HEAPSORT_HPP_
#define HEAPSORT_HPP_

#include <algorithm>

namespace sortutils {
using std::make_heap;
using std::sort_heap;

template <class RandomIterator> void heapsort(RandomIterator start, RandomIterator last) {
    make_heap(start, last);
    sort_heap(start, last);
}

}


#endif /* HEAPSORT_HPP_ */
