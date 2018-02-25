#include <data_structures/common/node.h>

template <typename T>
void Node<T>::setNode(std::shared_ptr<Node<T> > node, unsigned int i)
{
    if (i <= nodes_.size())
    {
        nodes_.at(i) = node;
        return;
    }
    std::cerr << "Index out of bounds for the node" << std::endl;
}

template <typename T>
void Node<T>::setValue(std::vector<T>& value)
{
    value_ = value;
}

template <typename T>
Node<T>::Node(std::vector<T>& value, unsigned int size) : nodes_(size, nullptr)
{
    value_ = value;
}

template <typename T>
Node<T>::Node(std::vector<T>* value, unsigned int size) : nodes_(size, nullptr)
{
    value_ = *value;
}

template <typename T>
T Node<T>::getValue(unsigned int i) const
{
    if (i <= value_.size())
        return value_.at(i);
    std::cerr << "Index out of bounds for the node" << std::endl;
}

template <typename T>
std::vector<T> Node<T>::getValues() const
{
    return value_;
}

template <typename T>
std::shared_ptr<Node<T> > Node<T>::getNode(unsigned int i) const
{
    if (i <= nodes_.size())
        return nodes_.at(i);
    std::cerr << "Index out of bounds for the node" << std::endl;
}

template <typename T>
Node<T>::~Node()
{

}
