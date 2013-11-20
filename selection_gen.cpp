#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

// After pivoting, we have:
// vec[0], vec[2], ..., vec[l-1] < pivot
// vec[l], vec[l+1], ..., vec[l+m-1] = pivot
// vec[l+m], vec[l+m+1], vec[-1] > pivot
// return the position (l,m)
// start+distance refers to the last position, exclusive
// Note: the return val might out of the index bound

/*
 * Return a true pivot index such that minimalize the recursive call
 */
template <class Iterator, class T=typename Iterator::value_type> inline size_t finalize_pivot(Iterator start, size_t l, size_t m, size_t len, const T& v) {
    // fill pivot values
    for (size_t i=0; i<m; ++i) {
        *(start+l+i) = v;
    }
    if (m==0 || l >= len/2) {
        return l;
    } else if (l+m < len/2) {
        return l+m;
    } else {
        return len/2;
    }
}


template <class Iterator, class T=typename Iterator::value_type> size_t pivot(const T& pivot_value, Iterator start, size_t distance) {
    size_t l = 0;
    size_t l_cur = 1;
    size_t r_cur = distance - 1;
    size_t m = 0;
    T val = *start;
    while (l_cur <= r_cur) { // ending condition: m = r-l
        if (val == pivot_value) {
            m++;
            while (l_cur<=r_cur) {
                T v = *(start+l_cur++);
                if (v != pivot_value) {
                    *(start+l) = v;
                    val = v;
                    break;
                } else { // (v == pivot) {
                    m++;
                }
            }
        }
        else if ( val > pivot_value) {
            //scan from r_cur to left until find element < pivot
            while (l_cur<=r_cur) {
                T v = *(start+r_cur);
                if (v>pivot_value) {
                    if (r_cur>0) {
                        --r_cur;
                    } else {
                        return finalize_pivot<Iterator, T>(start, l, m, distance, pivot_value);
                    }
                } else if (v == pivot_value) {
                    m++;
                    while (l_cur<=r_cur) {

                        T v = *(start+l_cur++);
                        if (v != pivot_value) {
                            *(start+r_cur) = v;
                            break;
                        } else { // (v == pivot) {
                            m++;
                        }
                    }
                } else {
                    *(start+(l++)) = v;
                    *(start+r_cur) = val;
                    if (l_cur == r_cur) {
                        ++l_cur;
                    } else {
                        val = *(start+l_cur++);
                        *(start + l) = val; // read next value
                    }
                    if (r_cur>0) {
                        --r_cur;
                        break;
                    } else {
                        return finalize_pivot<Iterator, T>(start, l, m, distance, pivot_value);
                    }
                }
            }
        }
        else {
            ++l;
            if (l_cur == r_cur) {
                ++l_cur;
            } else {
                val = *(start+l_cur++);
                *(start + l) = val; // read next value
            }
        }
    }
    return finalize_pivot<Iterator, T>(start, l, m, distance, pivot_value);
}


template <class Iterator> class IndexComparator {
    Iterator start;
    static unsigned index_table[5]; // for 5 group
public:
    IndexComparator(Iterator newStart) {
        start = newStart;
    }

    unsigned getMedian(Iterator newStart) {
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
template <class Iterator, class T=typename Iterator::value_type> T find_k(Iterator start, size_t num, size_t k) {
    if ((k==0) || (k>num)) throw "k should be greater than 0 and less or equal than num";

    if (num <=5){
        sort(start, start+num);
        return *(start+k-1);
    }

    T m = median_medians<Iterator, T>(start, num);

    size_t p = pivot(m, start, num); // partition the range with the median of medians

    if (p>=k) // how about p == num or p == 0?
        return find_k<Iterator, T>(start, p, k);
    else
        return find_k<Iterator, T>(start+p, num-p, k-p);
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

    return find_k<Iterator, T>(start, num_m, num_m/2);
}

int main(int argc, char** argv) {
    size_t m = 0;
    int *M = NULL;
    if (argc>2) {
        m = argc - 1;
        M = new int[m];
        for (size_t i = 1; i < argc; ++i) {
            M[i-1] = atoi(argv[i]);
        }
    } else {
        m = static_cast<size_t>(atoi(argv[1]));
        M = new int[m];
        srand (time(NULL));
        for (size_t i = 0; i < m; ++i) {
            M[i] = rand() % 100;
            // cout << ' ' << M[i];
        }
        cout << endl;
    }
   int mm = median_medians<int*, int>(M, m);
   cout << "First medians of medians: " <<  mm << endl;
   /*
   for (size_t i = 0; i < m; ++i) {
       cout << ' ' << M[i];
   }

   cout << endl;
   */
   size_t p = pivot<int*, int>(mm, M, m);
   cout << "Pivoting with mm return: " <<  p << endl;
   /*
   for (size_t i = 0; i < m; ++i) {
       cout << ' ' << M[i];
   }


   cout << endl;
    */
   cout << "Median: " <<  find_k<int*, int>(M, m, m/2) << endl;

   /*
   for (size_t i = 0; i < m; ++i) {
       cout << ' ' << M[i];
   }

   cout << endl;
    */
   vector<int> vec(m);
   for (size_t i = 0; i < m; ++i) {
         vec[i] = M[i];
         // cout << ' ' << vec[i];
   }
   cout << endl;

   cout << "Median of vec: " <<  find_k(vec.begin(), m, m/2) << endl;
   /*
   for (size_t i = 0; i < m; ++i) {
       cout << ' ' << vec[i];
   }
   cout << endl;
   */
   delete [] M;
   return 0;
  
}
