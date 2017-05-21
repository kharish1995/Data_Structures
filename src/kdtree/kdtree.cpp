#include <data_structures/kdtree/kdtree.h>

template <typename T>
KdTree<T>::KdTree(std::vector<std::vector<T> >& data, int children) : children_(children), data_(data)
{
    if(!data_.empty())
    {

    }
}

template <typename T>
KdTree<T>::~KdTree()
{

}
