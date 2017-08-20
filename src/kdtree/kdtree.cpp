#include <data_structures/kdtree/kdtree.h>

template <typename T>
KdTree<T>::KdTree(int cd) : cutDimension_(cd)
{

}

template <typename T>
KdTree<T>::~KdTree()
{

}

template <typename T>
bool KdTree<T>::insertNode(std::vector<T>& data)
{
    if(data_ == nullptr) { data_ = std::make_shared<Node<T> >(data, data.size()); dataDimension_ = data.size();}//shd look up

    if(insert(data, data_, cutDimension_) == nullptr)   return false;

    return true;
}

template <typename T>
std::shared_ptr<Node<T> > KdTree<T>::insert(std::vector<T>& data, std::shared_ptr<Node<T> > kd_node, int cd)
{
    if(kd_node == nullptr)  kd_node = std::make_shared<Node<T> >(data, dataDimension_);
    else if(data == kd_node->getValues());

    else if(data[cd] < kd_node->getValue(cd)) kd_node->getNode(0) = insert(data, kd_node->getNode(0), (cd+1) % dataDimension_);

    else    kd_node->getNode(1) = insert(data, kd_node->getNode(1), (cd+1) % dataDimension_);

    return kd_node;
}


template <typename T>
bool KdTree<T>::buildTree(std::vector<std::vector<T> >& data)
{
    for(auto& node_data : data)
        insertNode(node_data);

    return true;
}

template <typename T>
void KdTree<T>::findMin(std::vector<T>& minimum, int axis)
{
    if(data_ == nullptr) return;
     minimum = min(data_, axis, cutDimension_);
}

template <typename T>
std::vector<T> KdTree<T>::min(std::shared_ptr<Node<T> > kd_node, int axis, int cd)
{
    if (kd_node == nullptr);

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr) return kd_node->getValues();

        else return min(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        //shd look up minimum
        return minimum(min(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), min(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), kd_node->getValues(), axis);
}



template <typename T>
void KdTree<T>::findMax(std::vector<T>& maximum, int axis)
{
    if(data_ == nullptr) return;
    maximum = max(data_, axis, cutDimension_);
}


template <typename T>
std::vector<T> KdTree<T>::max(std::shared_ptr<Node<T> > kd_node, int axis, int cd)
{
    if (kd_node == nullptr);

    if (cd == axis)
    {
        if (kd_node->getNode(0) == nullptr) return kd_node->getValues();

        else return max(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
    }

    else
        //shd look up minimum
        return maximum(max(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), max(kd_node->getNode(0), axis, (cd + 1) % dataDimension_), kd_node->getValues(), axis);
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

//template <typename T>
//bool KdTree<T>::insertNode(std::vector<T>& data, int cd)
//{
//    if(data_.empty()) data_->value_ = data;

//    std::shared_ptr<Node<T> > temp_node = std::make_shared<Node<T> >(data_);

//    while(true)
//    {
//        if(data == temp_node->value_)    return false;

//        else if(data[cd] < temp_node->value_[cd])
//        {
//            if(temp_node->nodes_[0] == nullptr) {temp_node->nodes_[0] = std::make_shared<Node<T> >(data); return true;}
//            temp_node = temp_node->nodes_[0];
//            cd = (cd + 1) % data.size();
//        }

//        else
//        {
//            if(temp_node->nodes_[1] == nullptr) {temp_node->nodes_[1] = std::make_shared<Node<T> >(data); return true;}
//            temp_node = temp_node->nodes_[1];
//            cd = (cd + 1) % data.size();
//        }


//    }

//}

