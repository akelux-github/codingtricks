/*
 * selection.hpp
 *
 *  Created on: 2013-11-20
 *      Author: Rong Xiao
 */

#ifndef SELECTION_HPP_
#define SELECTION_HPP_

#include <algorithm>
#include <utility>

/*
#include <iostream>
using std::cout;
using std::endl;
*/

namespace selection {

using std::sort;
using std::pair;

/*
 * Fill pivot_value to [l, l+m) slots and return a good
 * pivot index, which is as close to the middle as possible.
 */
template <class Iterator, class T=typename Iterator::value_type> inline pair<size_t, size_t> finalize_pivot(Iterator start, size_t l, size_t m, size_t len, const T& v) {
    // fill pivot values
    T val = *(start+l);
    if (val>v) {
        *(start+l+m) = val;
    }

    for (size_t i=0; i<m; ++i) {
        *(start+l+i) = v;
    }
    /*
    cout << "After pivoting: " << endl;
    for (size_t i = 0; i<len; i++) {
        cout << ' ' << *(start+i);
    }
    cout << endl;
     */
    return pair<size_t, size_t>(l,m);
}

/*
    After pivoting before return, we have two value l, m such:
        vec[0], vec[2], ..., vec[l-1] < pivot
        vec[l], vec[l+1], ..., vec[l+m-1] = pivot_value
        vec[l+m], vec[l+m+1], vec[-1] > pivot_value
    Return the p such that:
        vec[0], vec[2], ..., vec[p-1] <= pivot_value and
        vec[p], vec[p+1], ... >= pivot_value

    Note:
        start+distance refers to the last position, exclusive
        the return p might out of the index bound
*/
template <class Iterator, class T=typename Iterator::value_type> pair<size_t, size_t> smart_pivot(const T& pivot_value, Iterator start, size_t len) {
    /*
    cout << "Before pivoting with: " << pivot_value << endl;
    for (size_t i = 0; i<len; i++) {
        cout << ' ' << *(start+i);
    }
    cout << endl;
    */
    size_t l = 0; // p[l-] < pivot_value
    size_t scanning_cur = 1; // scanning cursor
    size_t r = len - 1; // p[r+]>pivot_value
    size_t m = 0;
    T val = *start;
    while (scanning_cur <= r) { // Invariant: p[l-] < pivot_value, p[r+]>pivot_value, l+m<r
        // cout << "val: " << val <<"\t scanning_cur: " << scanning_cur <<"\t l: " << l << "\t r: " << r << endl;
        if (val == pivot_value) { // initializing s.t. start[l]!=pivot_value
            m++;
            while (scanning_cur<=r) {
                // cout << "val: " << val <<"\t scanning_cur: " << scanning_cur <<"\t l: " << l << "\t r: " << r << endl;

                T v = *(start+scanning_cur++);
                if (v != pivot_value) {
                    *(start+l) = v;
                    val = v;
                    break;
                } else { // (v == pivot) {
                    m++;
                }
            }
        } else if ( val > pivot_value) {
            //scan from r_cur to left until find element < pivot
            while (scanning_cur<=r) {
                // cout << "val: " << val <<"\t scanning_cur: " << scanning_cur <<"\t l: " << l << "\t r: " << r << endl;

                T v = *(start+r--); // Note r-- to ensure each index will be scan once and only once
                if (v>pivot_value) {

                } else if (v == pivot_value) {
                    m++;
                    while (scanning_cur<=r) {
                        // cout << "val: " << val <<"\t scanning_cur: " << scanning_cur <<"\t l: " << l << "\t r: " << r << endl;

                        T v = *(start+scanning_cur++);
                        if (v != pivot_value) {
                            *(start+r+1) = v;
                            break;
                        } else { // (v == pivot) {
                            m++;
                        }
                    }
                } else { // v < pivot_value and val > pivot_value
                    *(start+l++) = v;
                    *(start+r+1) = val;
                    if (scanning_cur == r) {
                        ++scanning_cur;
                    } else {
                        val = *(start+scanning_cur++);
                        *(start + l) = val; // read next value
                    }
                }
            }
        }
        else {
            ++l;
            if (scanning_cur == r) {
                // val = *(start+scanning_cur);
                ++scanning_cur;
            } else {
                val = *(start+scanning_cur++);
                *(start + l) = val; // read next value
            }
        }
    }
    return finalize_pivot<Iterator, T>(start, l, m, len, pivot_value);
}


template <class Iterator, class T=typename Iterator::value_type> inline size_t pivot(const T& pivot_value, Iterator start, size_t len) {
    pair<size_t, size_t> p = smart_pivot<Iterator, T>(pivot_value, start, len);
    size_t l = p.first;
    size_t m = p.second;
    if (m==0 || l >= len/2) {
        return l;
    } else if (l+m < len/2) {
        return l+m;
    } else {
        return len/2;
    }
}


template <class Iterator> class IndexComparator {
    Iterator start;
    static unsigned index_table[5]; // for 5 group
public:
    IndexComparator(Iterator newStart) {
        start = newStart;
        // cout << "Initializing a new IndexComparator instance" << endl;
    }

    unsigned getMedian(Iterator newStart) {
        // static size_t i(0);
        // i++;
        // cout << "Calling IndexComparator instance: " << i << endl;
        start = newStart;
        sort(index_table, index_table+5, *this);
        return index_table[2];
    }

    bool operator()(unsigned a, unsigned b){
        return (*(start+a) > *(start+b)) ? true : false;
    }
};

template <class Iterator> unsigned  IndexComparator<Iterator>::index_table[5] = {0, 1, 2, 3, 4};

template <class Iterator, class T=typename Iterator::value_type> T median_medians(Iterator start, size_t num);

// return the kth minimal element in the range start, start + num (not inclusive)
// ASSUME: 1<=k<=num
template <class Iterator, class T=typename Iterator::value_type> T select(Iterator start, size_t num, size_t k) {
    if ((k==0) || (k>num)) throw "k should be greater than 0 and less or equal than num";

    while (true) {
        if (num <=5){
            sort(start, start+num);
            return *(start+k-1);
        }

        T m = median_medians<Iterator, T>(start, num);

        size_t p = pivot(m, start, num); // partition the range with the median of medians

        if (p>=k) {// how about p == num or p == 0?
            num = p;
        } else {
            start = start + p;
            num -= p;
            k -= p;
        }
    }
}

template <class Iterator, class T=typename Iterator::value_type>
T median_medians(Iterator start, size_t num) {

    if (num == 0) {
        throw "0 size error in medians_medians";
    }

    if (num <=10){
        sort(start, start+num);
        return *(start+num/2);
    }

    static IndexComparator<Iterator> median_in_5(start);
    size_t num_m = num/5;

    // medians of groups of 5
    for(size_t i=0; i<num_m; i++) {
        unsigned m = median_in_5.getMedian(start+5*i);
        // swap median of the i-th 5 group to i-th position
        T val = *(start+i);
        *(start+i) = *(start+5*i+m);
        *(start+5*i+m) = val;
    }

    return select<Iterator, T>(start, num_m, num_m/2);
}
}
#endif /* SELECTION_HPP_ */
