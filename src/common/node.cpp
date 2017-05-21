#include <data_structures/common/node.h>

template <typename T>
Node<T>::Node(std::vector<T>& value, int size) : nodes_(size)
{
    value_ = value;
}


template <typename T>
Node<T>::~Node()
{
}
