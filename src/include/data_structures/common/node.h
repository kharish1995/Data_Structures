#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

template <typename T>           //template parameter declaration
class Node
{
    std::vector<T> value_;
    std::vector<std::shared_ptr<Node> > nodes_;

public:
    Node(std::vector<T>& , int size = 2);
    ~Node();
};

#endif // NODE_H
