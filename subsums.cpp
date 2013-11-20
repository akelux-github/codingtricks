/*
 * subsums.cpp
 *
 *  Created on: 2013-11-10
 *      Author: Rong Xiao
 */
#include <vector>

#include <cstdlib>
#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void computeSubsums(const vector<int>& vec, vector< vector<int> >& subsums) {
    size_t n = vec.size();
    for (size_t i = 0; i<n; i++) {
        subsums[i][0] = vec[i];
        for (size_t j=1; i+j<n; j++) {
            subsums[i][j] = subsums[i][j-1] + vec[i+j];
        }
    }
}

int main(int argc, char** argv) {
    size_t n = static_cast<size_t>(atoi(argv[1]));
    vector<int> vec(n);

    // cout << "Please input your " << m << " by " << n << " matrix row by row" << endl;
    srand (time(NULL));
    for (size_t i = 0; i < n; ++i) {
            vec[i] = rand() % 11 - 6;
            cout << ' ' << vec[i];
    }
    cout << endl;


    vector<vector<int> > subsums;
    for (size_t i = 0; i < n; ++i) {
        subsums.push_back(vector<int>(n-i));
    }

    computeSubsums(vec, subsums);

    for (size_t i = 0; i<n; i++) {
        for (size_t j=0; i+j<n; j++) {
            cout << ' ' << subsums[i][j];
        }
        cout << endl;
    }

    return 0;
}
