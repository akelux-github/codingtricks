/*
 * subsumtree.hpp
 *
 *  Created on: 2013-11-10
 *      Author: Rong Xiao
 */

#ifndef SUBSUMTREE_HPP_
#define SUBSUMTREE_HPP_

#include <vector>
using std::vector;

typedef vector<int>::size_type size_t; // size_t compatibility

struct BackTreeNode {
    BackTreeNode *parent;
    size_t lstart;
    size_t rend;
    int val;

    BackTreeNode(BackTreeNode *left, BackTreeNode *right) : lstart(left->lstart), rend(right->rend), val(left->val+right->val), parent(0)  {
        left->parent = this;
        right->parent=this;
    }

    BackTreeNode(int v, size_t i) : lstart(i), rend(i), val(v), parent(0) {
    }
};

class SubsumTree {

    vector<BackTreeNode*> treeNodes;


    void buildSubsumTree(const vector<int>& vec);
    void deleteSubsumTree();

public:
    SubsumTree(const vector<int>& vec);
    ~SubsumTree();
    int query(size_t i, size_t j);
};



#endif /* SUBSUMTREE_HPP_ */
