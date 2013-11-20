#include "selection.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace selection;

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

    cout << "Median: " <<  find_k<int*, int>(M, m, m/2) << endl;

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
