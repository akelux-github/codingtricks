/*
 * bubble.cpp
 *
 *  Created on: 2013-11-11
 *      Author: Rong Xiao
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

void bubble(int* arr, int n) {
    int swap = n-1;
    int count = 0;
    while(true) {
        int s = 0;
        for (int i = 0; i < swap; i++) {
            if (arr[i] > arr[i+1]) {
                int t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                s = i+1; // update swapped index
                count++;
            }
        }
        if ( s==0 ) {
            printf("Total swaps %d\n", count);
            break;
        } else {
            swap = s;
        }
    }
}

int quick_count = 0;
void quick(int* arr, int l, int r) {

    if (r-l<2) {
        return;
    }

    int p = arr[l]; // take the fisrt element as pivot
    int i = l+1; // all indices <i are <=p
    int j = r - 1; // all indices >j are >p
    for (; i<=j; ) {
        if (arr[i]>p) {
            while (i<=j && arr[j]>p) {
                j--;
            }
            if (i<j) {
                // swap arr[i], arr[j]
                int t = arr[i];
                arr[i++] = arr[j]; // increment j
                arr[j--] = t; // NOTE: decrement j
                quick_count++;
            }
        } else {
            i++;
        }
    }

    // i == j, i>j

        if ( i == r ) {
            i--; // now i = r-1
            if (arr[i]<p) { // a[l] is the maximum
                arr[l] = arr[i];
                arr[i] = p;
                quick_count++;
            }
            quick(arr, l, r-1);
        } else {
          quick(arr, l, i);
          quick(arr, i, r);
        }
}

int main(int argc, char** argv) {
    size_t m = static_cast<size_t>(atoi(argv[1]));
    // allocate mem for the mxn matrix
    int *M = new int[m];
    int *N = new int[m];


    // cout << "Please input the " << m << " numbers" << endl;
    srand (time(NULL));
    for (size_t i = 0; i < m; ++i) {
            M[i] = rand() % 100;
            N[i] = M[i];
            cout << ' ' << M[i];
    }
    cout << endl;

    bubble(M, m);
    quick(N, 0, m);
    cout << "After sort: " << endl;
    for (size_t i = 0; i < m; ++i) {
        cout << ' ' << M[i];
    }
    cout << endl;
    cout << "After sort: " << endl;
    for (size_t i = 0; i < m; ++i) {
        cout << ' ' << N[i];
    }
    
    cout << "\nquick_count " << quick_count << endl;

    delete [] M;
    delete [] N;

    return 0;
}
