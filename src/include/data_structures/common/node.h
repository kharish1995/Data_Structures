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
    std::vector<std::shared_ptr<Node<T> > > nodes_;

public:
    Node(std::vector<T>& , int size = 2);
    ~Node();
    T getValue(u_int8_t) const;
    std::vector<T> getValues() const;
    std::shared_ptr<Node<T> > getNode(u_int8_t) const;
};
template class Node<int>;
template class Node<float>;
template class Node<double>;
#endif // NODE_H
