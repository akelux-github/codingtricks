/*
 * minstack.hpp
 *
 *  Created on: 2013-11-18
 *      Author: Rong Xiao
 */

#ifndef MINSTACK_HPP_
#define MINSTACK_HPP_
#include <vector>
#include <stack>
using std::vector;
using std::stack;

/*
 * A stack template that has constant time for operations: push, pop, and min.
 */
template <class T> class MinStack : public stack<T, vector<T> > {
    vector<T> _mins; // keep track of minimum on the very back
public:
    MinStack() : stack<T, vector<T> >(), _mins() {

    }

    void push(const T& val) {
        if (empty()) {
            _mins.push_back(val);
        } else {
            curMin = _mins.back();
            _mins.push_back(val<curMin ? val : curMin);
        }
        stack<T, vector<T> >::push(val);
    }

    void pop(const T& val) {
        stack<T, vector<T> >::pop(val);
        _mins.pop_back();
    }

    T min() {
        return _mins.back();
    }

};



#endif /* MINSTACK_HPP_ */
