/*
 * bucketsort_test.cpp
 *
 *  Created on: 2013-11-21
 *      Author: Rong Xiao
 */


/*
 * heapsort_test.cpp
 *
 *  Created on: 2013-11-21
 *      Author: Rong Xiao
 */
#include "bucketsort.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

size_t id(const int& x) {
    return static_cast<size_t>(x);
}

int main(int argc, char** argv) {
    size_t m = 0;
    vector<int> *M = NULL;
    if (argc>2) {
        m = argc - 1;
        M = new vector<int>(m);
        for (size_t i = 1; i < argc; ++i) {
            (*M)[i-1] = atoi(argv[i]);
            // cout << ' ' << (*M)[i-1];
        }
        cout << endl;
    } else {
        m = static_cast<size_t>(atoi(argv[1]));
        M = new vector<int>(m);
        srand (time(NULL));
        for (size_t i = 0; i < m; ++i) {
            (*M)[i] = rand() % 100;
            // cout << ' ' << (*M)[i];
        }
        cout << endl;
    }

    sortutils::KeyOrder<int> keyorder(id, 100);
    clock_t begin = clock();


    sortutils::bucketsort<vector<int>::iterator, int, sortutils::KeyOrder<int> >(M->begin(), M->begin()+m, keyorder);


    cout << "Sort timing: "<< double(clock() - begin) / CLOCKS_PER_SEC << endl;


    /*
    cout << "After sort: " << endl;

    for (size_t i = 0; i < m; ++i) {
        cout << ' ' << (*M)[i];
    }


    cout << endl;

    */
    delete M;
    return 0;
}





