#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <data_structures/common/node.h>

template <typename T>
class KdTree
{
    std::vector<std::vector<T> > data_;
    int children_;
public:
    KdTree(std::vector<std::vector<T> >& , int children = 2);
    ~KdTree();
    bool insertNode(std::vector<T>& );
    bool deleteNode(std::vector<T>& );
    void findMin(std::vector<T>& , int axis);
    void findMax(std::vector<T>& , int axis);
};

#endif // KDTREE_H
