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
    if(data_.empty()) { data_->value_ = data; dataDimension_ = data.size();}//shd look up
    return insert(data, data_, cutDimension_);
}

template <typename T>
bool KdTree<T>::insert(std::vector<T>& data, std::shared_ptr<Node<T> > kd_node, int cd)
{
    if(kd_node == nullptr)  kd_node = std::make_shared<Node<T> >(data);

    else if(data == kd_node->value_)   return false;

    else if(data[cd] < kd_node->value_[cd]) kd_node->nodes_[0] = insert(data, kd_node->nodes_[0], (cd+1) % dataDimension_);

    else    kd_node->nodes_[1] = insert(data, kd_node->nodes_[1], (cd+1) % dataDimension_);

    return true;
}


template <typename T>
bool KdTree<T>::buildTree(std::vector<std::vector<T> >& data)
{
    for(const auto& node_data : data)
        insertNode(node_data);
}

template <typename T>
void KdTree<T>::findMin(std::vector<T>& minimum, int axis)
{
    if(data_.empty()) return;
     minimum = min(data_, axis, cutDimension_);
}

template <typename T>
std::vector<T>& KdTree<T>::min(std::shared_ptr<Node<T> > kd_node, int axis, int cd)
{
    if (kd_node == nullptr) return;
    // T splits on the dimension we’re searching
    // => only visit left subtree
    if (cd == axis)
    if (kd_node->nodes_[0] == nullptr) return kd_node->value_;

    else return min(kd_node->nodes_[0], axis, (cd+1) % dataDimension_);
    // T splits on a different dimension
    // => have to search both subtrees
    else
        //shd look up minimum
        return std::min({min(kd_node->nodes_[0], axis, (cd + 1) % dataDimension_), min(kd_node->nodes_[0], axis, (cd + 1) % dataDimension_), kd_node->value_});
}

template <typename T>
void KdTree<T>::findMax(std::vector<T>& maximum, int axis)
{
    if(data_.empty()) return;
    maximum = max(data_, axis, cutDimension_);
}

template <typename T>
std::vector<T>& KdTree<T>::max(std::shared_ptr<Node<T> > kd_node, int axis, int cd)
{
    if (kd_node == nullptr) return;
    // T splits on the dimension we’re searching
    // => only visit left subtree
    if (cd == axis)
    if (kd_node->nodes_[0] == nullptr) return kd_node->value_;

    else return max(kd_node->nodes_[0], axis, (cd+1) % dataDimension_); //shd change
    // T splits on a different dimension
    // => have to search both subtrees
    else
        //shd look up maximum
        return std::max({max(kd_node->nodes_[0], axis, (cd + 1) % dataDimension_), max(kd_node->nodes_[0], axis, (cd + 1) % dataDimension_), kd_node->value_[axis]});
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

