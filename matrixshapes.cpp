/*
 * matrixshapes.cpp
 *
 *  Created on: 2013-11-09
 *      Author: Rong Xiao
 */

/*
 * Count the shapes in mxn integer matrix M
 * A shape is a 'continuous' region in the matrix consists of the same number
 */
#include <utility>
#include <bitset>
#include <stack>
#include <vector>

#include <cstdlib>
#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

using std::pair;
using std::bitset;
using std::stack;
using std::vector;


typedef pair<size_t, size_t> Index;

/*
 * visit all indices in the shape containing i, add un visited indices adjacent to the shape to startings stack,
 * for future exploring
 */
void exploreShape(const Index& i, int** M, size_t m, size_t n, vector< vector<bool> >& visited, stack<Index>& startings) {

    int val = M[i.first][i.second];
    stack<Index> toExplore;

    visited[i.first][i.second] = true; // mark index i as visited
    toExplore.push(i); // add i to be explored for neighbors
    size_t count = 1;
    while(true) {
        if (toExplore.empty()) {
            break;
        }

        Index j = toExplore.top();
        toExplore.pop();
        size_t x = j.first;
        size_t y = j.second;

        // check all 8 neighbors of i
        if (x+1<m) {
            if (!visited[x+1][y]) {
                if (val == M[x+1][y]) {
                    visited[x+1][y]= true;
                    toExplore.push(Index(x+1,y));
                    ++count;
                } else {
                    startings.push(Index(x+1,y));
                }
            }

            if (y+1<n && !visited[x+1][y+1]) {
                if (val == M[x+1][y+1]) {
                    visited[x+1][y+1] = true;
                    toExplore.push(Index(x+1,y+1));
                    ++count;
                } else {
                    startings.push(Index(x+1,y+1));
                }
            }

            if (y>0 && !visited[x+1][y-1]) {
                if (val == M[x+1][y-1]) {
                    visited[x+1][y-1] = true;
                    toExplore.push(Index(x+1,y-1));
                    ++count;
                } else {
                    startings.push(Index(x+1,y-1));
                }
            }
        }

        if (x>0) {
            if (!visited[x-1][y]) {
                if (val == M[x-1][y]) {
                    visited[x-1][y] = true;
                    toExplore.push(Index(x-1,y));
                    ++count;
                } else {
                    startings.push(Index(x-1,y));
                }
            }

            if (y+1<n && !visited[x-1][y+1]) {
                if (val == M[x-1][y+1]) {
                    visited[x-1][y+1] = true;
                    toExplore.push(Index(x-1,y+1));
                    ++count;
                } else {
                    startings.push(Index(x-1,y+1));
                }
            }

            if (y>0 && !visited[x-1][y-1]) {
                if (val == M[x-1][y-1]) {
                    visited[x-1][y-1] = true;
                    toExplore.push(Index(x-1,y-1));
                    ++count;
                } else {
                    startings.push(Index(x-1,y-1));
                }
            }
        }

        if (y+1<n && !visited[x][y+1]) {
            if (val == M[x][y+1]) {
                visited[x][y+1]= true;
                toExplore.push(Index(x,y+1));
                ++count;
            } else {
                startings.push(Index(x,y+1));
            }
        }

        if (y>0 && !visited[x][y-1]) {
            if (val == M[x][y-1]) {
                visited[x][y-1] = true;
                toExplore.push(Index(x,y-1));
                ++count;
            } else {
                startings.push(Index(x,y-1));
            }
        }
    }

    // cout << '(' << i.first << ", " << i.second << ") has " << count << endl;
}

/*
 * count number of shapes
 * Complexity: O(m*n) time and space, each index will be checked at most 9 times
 */
size_t countShapes(int** M, size_t m, size_t n) {
    //maintain potential start index stack, with initial index [0][0]
    stack<Index> startings;
    startings.push(Index(0,0));
    // visited marks
    vector< vector<bool> > visited(m, vector<bool>(n, false));
    size_t count = 0;
    while (true) {
        if (startings.empty()) {
            break;
        }

        Index i = startings.top();
        startings.pop();
        if (!visited[i.first][i.second]) {
            ++count;
            exploreShape(i, M, m, n, visited, startings); // visit all indices in the shape containing i
        }
    }
    return count;
}


int main(int argc, char** argv) {
    size_t m = static_cast<size_t>(atoi(argv[1]));
    size_t n = static_cast<size_t>(atoi(argv[2]));
    // allocate mem for the mxn matrix
    int **M = new int*[m];
    for (size_t i = 0; i < m; ++i) {
        M[i] = new int[n];
    }

    // cout << "Please input your " << m << " by " << n << " matrix row by row" << endl;
    srand (time(NULL));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            // cin >> M[i][j];
            M[i][j] = rand() % 10;
            // cout << ' ' << M[i][j];
        }
        // cout << endl;
    }


    cout << "There are " << countShapes(M, m, n) << " shapes" << endl;

    // free matrix mem
    for (size_t i = 0; i < m; ++i) {
        delete [] M[i];
    }

    delete [] M;

    return 0;
}
