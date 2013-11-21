/*
 * qsort.hpp
 *
 *  Created on: 2013-11-20
 *      Author: Rong Xiao
 */

#ifndef QSORT_HPP_
#define QSORT_HPP_

#include "selection.hpp"


namespace sortutils {

using selection::smart_pivot;
using selection::select;
using std::pair;
template <class Iterator, class T=typename Iterator::value_type>
inline void qsort(Iterator start, size_t len ) {
    if (len < 2) {
        return;
    }

    T pivot = select<Iterator, T>(start, len, len/2);

    pair<size_t, size_t> p = smart_pivot<Iterator, T>(pivot, start, len);


    size_t l = p.first;
    size_t m = p.second;
    if (l+m>len) {
        throw "Something wrong happen inside smart_pivot!";
    }
    qsort<Iterator, T>(start, l);
    qsort<Iterator, T>(start+l+m, (len-l-m));
}

}

#endif /* QSORT_HPP_ */
