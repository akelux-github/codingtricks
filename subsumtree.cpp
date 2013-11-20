/*
 * subsumstree.cpp
 *
 *  Created on: 2013-11-10
 *      Author: Rong Xiao
 */
#include "subsumtree.hpp"

#include <forward_list>



#include <cstdlib>
#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

using std::forward_list;

void SubsumTree::buildSubsumTree(const vector<int>& vec)  {
    for (size_t i = 0; i<vec.size(); ++i) {
        treeNodes.push_back(new BackTreeNode(vec[i], i));
    }

    forward_list<BackTreeNode*> buildingLayer;
    forward_list<BackTreeNode*>::iterator it = buildingLayer.before_begin();
    size_t n = treeNodes.size();
    for (size_t i =0; true; ) {
        if (i==n) {
            break;
        }
        else if (i+1<n) {
            it = buildingLayer.insert_after(it, new BackTreeNode(treeNodes[i], treeNodes[i+1]));
            i += 2;
        } else {
            it = buildingLayer.insert_after(it, treeNodes[i]);
            i++;
        }
    }

    size_t height = 1;
    /*
    cout << "Building layer: | ";

    for (forward_list<BackTreeNode*>::iterator tmp = buildingLayer.begin(); tmp != buildingLayer.end(); tmp++) {
        cout << " -> " << (*tmp)->val;
    }
    cout << endl;
     */

    while (true) {
        forward_list<BackTreeNode*>::iterator cur = buildingLayer.before_begin();
        forward_list<BackTreeNode*>::iterator it = buildingLayer.begin();
        if (++it == buildingLayer.end()) {
            break;
        } else {
            it = buildingLayer.begin();
        }

        while(it!=buildingLayer.end() && ++it!=buildingLayer.end()) {
            forward_list<BackTreeNode*>::iterator it1 = cur;
            it1++;
            cur=buildingLayer.insert_after(cur, new BackTreeNode(*it1, *it));
            it = buildingLayer.erase_after(cur);
            it = buildingLayer.erase_after(cur);
        }

        /*
        cout << "Building layer: | ";

        for (forward_list<BackTreeNode*>::iterator tmp = buildingLayer.begin(); tmp != buildingLayer.end(); tmp++) {
            cout << " -> " << (*tmp)->val;
        }
        cout << endl;
        */
        height ++ ;
    }

    cout << "Tree heigth is " << height << endl;
}

SubsumTree::SubsumTree(const vector<int>& vec) : treeNodes() {
    buildSubsumTree(vec);
    /*
    for (size_t i = 0; i<treeNodes.size(); ++i) {
            cout <<' '<< reinterpret_cast<size_t>(treeNodes[i]->parent);
    }
    cout << endl;
    */
}

void SubsumTree::deleteSubsumTree() {
    for (size_t i = 0; i<treeNodes.size(); ++i) {
        BackTreeNode* t = treeNodes[i];
        while (t) {
            BackTreeNode* tmp = t->parent;
            if (tmp && t->lstart == tmp->lstart) {
                delete t;
                t = tmp;
            } else {
                delete t;
                t = 0;
            }
        }
    }
}

SubsumTree::~SubsumTree() {
    deleteSubsumTree();
}

int SubsumTree::query(size_t i, size_t j) {
    j--;
    BackTreeNode* t = treeNodes[i];
    int diff = 0;
    while (t->rend<j) { // t &&
        BackTreeNode* tmp = t->parent;
        if (t->rend == tmp->rend) {
            diff += (tmp->val - t->val);
        }
        t = tmp;
    }

    t = treeNodes[j];

    while (t->lstart>i) { // t &&
        BackTreeNode* tmp = t->parent;
        if (t->lstart == tmp->lstart) {
            diff += (tmp->val - t->val);
        }
        t = tmp;
    }

    return t->val - diff;

}

int main(int argc, char** argv) {
    size_t n = static_cast<size_t>(atoi(argv[1]));
    vector<int> vec(n);

    // cout << "Please input your " << m << " by " << n << " matrix row by row" << endl;
    srand (time(NULL));
    for (size_t i = 0; i < n; ++i) {
            vec[i] = rand() % 11 - 6;
            // cout << ' ' << vec[i];
    }
    // cout << endl;


    SubsumTree subsums(vec);

    while (true) {
        size_t i;
        size_t j;
        cout << "Input the start and end index to query " << endl;
        cin >> i;
        cin >> j;
        if (i>=j || j>vec.size()) { // i<0 no need to check
            break;
        } else {
            cout << "Sub sum is " << subsums.query(i,j) << endl;
        }
    }


    return 0;
}

