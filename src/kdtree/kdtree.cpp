#include <data_structures/kdtree/kdtree.h>

template <typename T>
KdTree<T>::KdTree()
{
    data_ = nullptr;
    cutDimension_ = 0;
}

template <typename T>
KdTree<T>::KdTree(unsigned int cd) : cutDimension_(cd)
{
    data_ = nullptr;
}

template <typename T>
KdTree<T>::KdTree(std::vector<T>& data, unsigned int cd) : cutDimension_(cd)
{
    data_ = std::make_shared<Node<T> >(data, data.size());
}

template <typename T>
bool KdTree<T>::insert(std::vector<T>& data)
{

    if(data.empty()){
        std::cerr << "Empty point provided!!" << '\n';
        return false;
    }
    if(data_ == nullptr){
        data_ = std::make_shared<Node<T> >(data, data.size());
        dataDimension_ = data.size();
        return true;
    }

    if(insertNode(data, data_, cutDimension_) == nullptr)
        return false;

    return true;
}

template <typename T>
bool KdTree<T>::insert(std::vector<T>&& data)
{
    if(data.empty()){
        std::cerr << "Empty point provided!!" << '\n';
        return false;
    }
    if(data_ == nullptr){
        data_ = std::make_shared<Node<T> >(data, data.size());
        dataDimension_ = data.size();
        return true;
    }

    if(insertNode(data, data_, cutDimension_) == nullptr)
        return false;

    return true;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::insertNode(std::vector<T>& data,
                                                std::shared_ptr<Node<T> > kd_node,
                                                unsigned int cd)
{
    if(kd_node == nullptr)  kd_node = std::make_shared<Node<T> >(data, dataDimension_);

    else if(data == kd_node->getValues())
        return nullptr;

    else if(data.at(cd) < kd_node->getValue(cd))
        kd_node->setNode(insertNode(data, kd_node->getNode(0), (cd+1) % dataDimension_), 0);

    else
        kd_node->setNode(insertNode(data, kd_node->getNode(1), (cd+1) % dataDimension_), 1);

    return kd_node;
}

template <typename T>
bool KdTree<T>::build(std::vector<std::vector<T> >& data)
{
    for(auto& node_data : data)
        insert(node_data);

    return true;
}

template <typename T>
bool KdTree<T>::build(std::vector<std::vector<T> >&& data)
{
    for(auto& node_data : data)
        insert(node_data);

    return true;
}

template <typename T>
void KdTree<T>::min(std::vector<T>& minimum,
                         unsigned int axis)
{
    if(data_ == nullptr) return;
     minimum = (minNode(data_, axis, cutDimension_))->getValues();
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::minNode(std::shared_ptr<Node<T> > kd_node,
                                             unsigned int axis,
                                             unsigned int cd)
{
    if (kd_node == nullptr)
        return nullptr;

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr)
            return kd_node;

        return minNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        return minimum(minNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                       minNode(kd_node->getNode(1), axis, (cd + 1) % dataDimension_),
                       kd_node,
                       axis);
}

template <typename T>
void KdTree<T>::max(std::vector<T>& maximum,
                         unsigned int axis)
{
    if(data_ == nullptr) return;
    maximum = (maxNode(data_, axis, cutDimension_))->getValues();
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::maxNode(std::shared_ptr<Node<T> > kd_node,
                                             unsigned int axis,
                                             unsigned int cd)
{
    if (kd_node == nullptr)
        return nullptr;

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr)
            return kd_node;

        return maxNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        return maximum(maxNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                       maxNode(kd_node->getNode(1), axis, (cd + 1) % dataDimension_),
                       kd_node,
                       axis);
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::minimum(std::shared_ptr<Node<T> > node1,
                                             std::shared_ptr<Node<T> > node2,
                                             std::shared_ptr<Node<T> > node3,
                                             unsigned int axis)
{
    if(node1 == nullptr && node2 == nullptr)
        return node3;

    else if(node1 == nullptr)
        if(node2->getValue(axis) < node3->getValue(axis))
            return node2;

    else if(node2 == nullptr)
            if(node1->getValue(axis) < node3->getValue(axis))
                return node1;

    return node3;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::maximum(std::shared_ptr<Node<T> > node1,
                                             std::shared_ptr<Node<T> > node2,
                                             std::shared_ptr<Node<T> > node3,
                                             unsigned int axis)
{
    if(node1 == nullptr && node2 == nullptr)
        return node3;

    else if(node1 == nullptr)
        if(node2->getValue(axis) > node3->getValue(axis))
            return node2;

    else if(node2 == nullptr)
            if(node1->getValue(axis) > node3->getValue(axis))
                return node1;

    return node3;
}

template <typename T>
bool KdTree<T>::erase(std::vector<T>& data)
{
    if(data_ == nullptr){
        std::cerr << "Sorry, Tree not built yet!!" << '\n';
        return false;
    }

    if(data.empty()){
        std::cerr << "Empty point provided!!" << '\n';
        return false;
    }

    if((data_->getNode(0) == nullptr) && (data_->getNode(1) == nullptr))
        data_ = nullptr;

    else if(deleteNode(data, data_, cutDimension_) == nullptr){
        std::cout << "Point not found" << '\n';
        return false;
    }

    return true;
}

template <typename T>
bool KdTree<T>::erase(std::vector<T>&& data)
{
    if(data_ == nullptr){
        std::cerr << "Sorry, Tree not built yet!!" << '\n';
        return false;
    }

    if(data.empty()){
        std::cerr << "Empty point provided!!" << '\n';
        return false;
    }

    if((data_->getNode(0) == nullptr) && (data_->getNode(1) == nullptr))
        data_ = nullptr;

    else if(deleteNode(data, data_, cutDimension_) == nullptr){
        std::cout << "Point not found" << '\n';
        return false;
    }

    return true;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::deleteNode(std::vector<T> data,
                                                std::shared_ptr<Node<T> > kd_node,
                                                unsigned int axis)
{
    if (kd_node == nullptr)
        return nullptr;

    unsigned int new_axis = (axis + 1) % dataDimension_;

    if(data == kd_node->getValues()){
        if(kd_node->getNode(1) != nullptr){
            auto min1 = minNode(kd_node->getNode(1), axis, new_axis)->getValues();
            kd_node->setValue(min1);
            kd_node->setNode(deleteNode(kd_node->getValues(), kd_node->getNode(1), new_axis), 1);
    }

        else if(kd_node->getNode(0) != nullptr){
            auto min0 = minNode(kd_node->getNode(0), axis, new_axis)->getValues();
            kd_node->setValue(min0);
            kd_node->setNode(deleteNode(kd_node->getValues(), kd_node->getNode(0), new_axis), 1);
    }
        else
            kd_node = nullptr;
    }
    else if (data.at(axis) < kd_node->getValue(axis))
        kd_node->setNode(deleteNode(data, kd_node->getNode(0), new_axis), 0);

    else
        kd_node->setNode(deleteNode(data, kd_node->getNode(1), new_axis), 1);

    return kd_node;
}

template <typename T>
bool KdTree<T>::find(std::vector<T>& data)
{
    if(data_ == nullptr){
        std::cerr << "Sorry, Tree not built yet!!" << '\n';
        return false;
    }

    if(data.empty()){
        std::cerr << "Empty point provided!!" << '\n';
        return false;
    }

    if(findNode(data, data_, cutDimension_) == nullptr){
        std::cout << "Point not found" << '\n';
        return false;
    }

    return true;
}

template <typename T>
bool KdTree<T>::find(std::vector<T>&& data)
{
    if(data_ == nullptr){
        std::cerr << "Sorry, Tree not built yet!!" << '\n';
        return false;
    }

    if(data.empty()){
        std::cerr << "Empty point provided!!" << '\n';
        return false;
    }

    if(findNode(data, data_, cutDimension_) == nullptr){
        std::cout << "Point not found" << '\n';
        return false;
    }

    return true;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::findNode(std::vector<T> data,
                                              std::shared_ptr<Node<T> > kd_node,
                                              unsigned int axis)
{
    if (kd_node == nullptr)
        return nullptr;

    int new_axis = (axis + 1) % dataDimension_;

    if(data == kd_node->getValues())
        return kd_node;

    else if (data.at(axis) < kd_node->getValue(axis))
        kd_node = findNode(data, kd_node->getNode(0), new_axis);

    else
        kd_node = findNode(data, kd_node->getNode(1), new_axis);

    return kd_node;
}

template <typename T>
void KdTree<T>::visualizeTree(std::shared_ptr<Node<T> > node, int space)
{
    if(node == nullptr)
        return;
    space += 10;

    visualizeTree(node->getNode(1), space);
    std::cout << '\n';

    for(unsigned int i = 10; i < space; ++i)
        std::cout << " ";

    for(const auto& i : node->getValues())
        std::cout << i << " ";

    visualizeTree(node->getNode(0), space);
    std::cout << '\n';
}

template <typename T>
void KdTree<T>::view()
{
    visualizeTree(data_, 0);
}

template <typename T>
KdTree<T>::~KdTree()
{

}

