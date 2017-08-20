#include <data_structures/kdtree/kdtree.h>

template <typename T>
KdTree<T>::KdTree(int cd) : cutDimension_(cd)
{

}

template <typename T>
KdTree<T>::KdTree(std::vector<T> data, int cd) : cutDimension_(cd)
{
    data_ = std::make_shared<Node<T> >(data, data.size());
}

template <typename T>
KdTree<T>::~KdTree()
{

}

template <typename T>
bool KdTree<T>::insert_node(std::vector<T>& data)
{
    if(data_ == nullptr){
        data_ = std::make_shared<Node<T> >(data, data.size());
        dataDimension_ = data.size();
    }//shd look up

    if(insertNode(data, data_, cutDimension_) == nullptr)   return false;

    return true;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::insertNode(std::vector<T>& data, std::shared_ptr<Node<T> > kd_node, int cd)
{
    if(kd_node == nullptr)  kd_node = std::make_shared<Node<T> >(data, dataDimension_);

    else if(data == kd_node->getValues()) return nullptr;

    else if(data[cd] < kd_node->getValue(cd))
        kd_node->getNode(0) = insertNode(data, kd_node->getNode(0), (cd+1) % dataDimension_);

    else
        kd_node->getNode(1) = insertNode(data, kd_node->getNode(1), (cd+1) % dataDimension_);

    return kd_node;
}


template <typename T>
bool KdTree<T>::buildTree(std::vector<std::vector<T> >& data)
{
    for(auto& node_data : data)
        insert_node(node_data);

    return true;
}

template <typename T>
void KdTree<T>::find_min(std::vector<T>& minimum, int axis)
{
    if(data_ == nullptr) return;
     minimum = minNode(data_, axis, cutDimension_);
}

template <typename T>
std::vector<T> KdTree<T>::minNode(std::shared_ptr<Node<T> > kd_node, int axis, int cd)
{
    if (kd_node == nullptr);

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr) return kd_node->getValues();

        else return minNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        //shd look up minimum
        return minimum(minNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), minNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), kd_node->getValues(), axis);
}



template <typename T>
void KdTree<T>::find_max(std::vector<T>& maximum, int axis)
{
    if(data_ == nullptr) return;
    maximum = maxNode(data_, axis, cutDimension_);
}


template <typename T>
std::vector<T> KdTree<T>::maxNode(std::shared_ptr<Node<T> > kd_node, int axis, int cd)
{
    if (kd_node == nullptr);

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr) return kd_node->getValues();

        else return maxNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        //shd look up minimum
        return maximum(maxNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), maxNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), kd_node->getValues(), axis);
}

template <typename T>
std::vector<T> KdTree<T>::minimum(std::vector<T> value1, std::vector<T> value2, std::vector<T> value3, int axis)
{
    if(value1.empty() && value2.empty()) return value3;

    else if(value1.empty()) if(value2[axis] < value3[axis]) return value2;

    else if(value2.empty()) if(value1[axis] < value3[axis]) return value1;

    return value3;
}

template <typename T>
std::vector<T> KdTree<T>::maximum(std::vector<T> value1, std::vector<T> value2, std::vector<T> value3, int axis)
{
    if(value1.empty() && value2.empty()) return value3;

    else if(value1.empty()) if(value2[axis] > value3[axis]) return value2;

    else if(value2.empty()) if(value1[axis] > value3[axis]) return value1;

    return value3;
}

template <typename T>
bool KdTree<T>::delete_node(std::vector<T>& data)
{

}

template <typename T>
std::vector<T> KdTree<T>::deleteNode(std::vector<T>& data, std::shared_ptr<Node<T> > kd_node, int axis)
{
    if (kd_node == nullptr);

    int new_axis = (axis + 1) % dataDimension_;

    if(data == kd_node->getValues())
        if(kd_node->getNode(1) != NULL);
}



