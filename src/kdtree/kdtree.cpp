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
std::shared_ptr<Node<T> > KdTree<T>::insertNode(std::vector<T>& data,
                                                std::shared_ptr<Node<T> > kd_node,
                                                int cd)
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
void KdTree<T>::find_min(std::vector<T>& minimum,
                         int axis)
{
    if(data_ == nullptr) return;
     minimum = minNode(data_, axis, cutDimension_);
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::minNode(std::shared_ptr<Node<T> > kd_node,
                                             int axis,
                                             int cd)
{
    if (kd_node == nullptr) return nullptr;

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr) return kd_node;

        return minNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        //shd look up minimum
        return minimum(minNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                       minNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                       kd_node->getValues(), axis);
}



template <typename T>
void KdTree<T>::find_max(std::vector<T>& maximum,
                         int axis)
{
    if(data_ == nullptr) return;
    maximum = maxNode(data_, axis, cutDimension_);
}


template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::maxNode(std::shared_ptr<Node<T> > kd_node,
                                             int axis,
                                             int cd)
{
    if (kd_node == nullptr) return nullptr;

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr) return kd_node;

        return maxNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        //shd look up minimum
        return maximum(maxNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                       maxNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                       kd_node->getValues(), axis);
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::minimum(std::shared_ptr<Node<T> > node1,
                                             std::shared_ptr<Node<T> > node2,
                                             std::shared_ptr<Node<T> > node3,
                                             int axis)
{
    if((node1->getValues()).empty() && (node2->getValues()).empty())
        return node3;

    else if((node1->getValues()).empty())
        if(node2->getValue(axis) < node3->getValue(axis))
            return node2;

    else if((node1->getValues()).empty())
            if(node2->getValue(axis) < node3->getValue(axis))
                return node1;

    return node3;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::maximum(std::shared_ptr<Node<T> > node1,
                                             std::shared_ptr<Node<T> > node2,
                                             std::shared_ptr<Node<T> > node3,
                                             int axis)
{
    if((node1->getValues()).empty() && (node2->getValues()).empty())
        return node3;

    else if((node1->getValues()).empty())
        if(node2->getValue(axis) > node3->getValue(axis))
            return node2;

    else if((node1->getValues()).empty())
            if(node2->getValue(axis) > node3->getValue(axis))
                return node1;

    return node3;
}

template <typename T>
bool KdTree<T>::delete_node(std::vector<T>& data)
{
    if(data_ == nullptr)
        std::cerr << "Sorry, Tree not built yet!!" << std::endl;

    if(data.empty())
        std::cerr << "Empty point provided!!" << std::endl;

    if(deleteNode(data, data_, cutDimension_) == nullptr){
        std::cout << "Point not found" << std::endl;
        return false;
    }

    return true;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::deleteNode(std::vector<T> data,
                                                std::shared_ptr<Node<T> > kd_node,
                                                int axis)
{
    if (kd_node == nullptr)
        return nullptr;

    int new_axis = (axis + 1) % dataDimension_;

    if(data == kd_node->getValues()){
        if(kd_node->getNode(1) != nullptr){
            kd_node->setValue(minNode(kd_node->getNode(1), axis, new_axis));
            kd_node->setNode(deleteNode(kd_node->getValues(), kd_node->getNode(1), new_axis), 1);
    }

        else if(kd_node->getNode(0) != nullptr){
            kd_node->setValue(minNode(kd_node->getNode(0), axis, new_axis));
            kd_node->setNode(deleteNode(kd_node->getValues(), kd_node->getNode(0), new_axis), 1);
    }
        else
            kd_node = nullptr;
    }
    else if (data[axis] < kd_node->getValue(axis))
        kd_node->setNode(deleteNode(data, kd_node->getNode(0), new_axis), 0);

    else
        kd_node->setNode(deleteNode(data, kd_node->getNode(1), new_axis), 1);

    return kd_node;
}

template <typename T>
KdTree<T>::~KdTree()
{

}

