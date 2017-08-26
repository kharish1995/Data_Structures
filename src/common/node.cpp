#include <data_structures/common/node.h>

template <typename T>
void Node<T>::setNode(const std::shared_ptr<Node<T> >& node, u_int8_t i)
{
    if (i > nodes_.size())
        std::cerr << "Index out of bounds for the node" << std::endl;
    nodes_[i] = node;
}

template <typename T>
void Node<T>::setValue(const std::vector<T>& value)
{
    value_ = value;
}

template <typename T>
Node<T>::Node(std::vector<T>& value, int size) : nodes_(size, nullptr)
{
    value_ = value;
}

template <typename T>
Node<T>::Node(std::vector<T>* value, int size) : nodes_(size, nullptr)
{
    value_ = *value;
}

template <typename T>
T Node<T>::getValue(u_int8_t i) const
{
    if (i > value_.size())
        std::cerr << "Index out of bounds for the node" << std::endl;
    return value_[i];
}

template <typename T>
std::vector<T> Node<T>::getValues() const
{
    return value_;
}

template <typename T>
std::shared_ptr<Node<T> > Node<T>::getNode(u_int8_t i) const
{
    if (i > nodes_.size())
        std::cerr << "Index out of bounds for the node" << std::endl;
    return nodes_[i];
}

template <typename T>
Node<T>::~Node()
{
}
