/*
 * This code is developed to implement the KdTree data structure
 * The authors of this code are Harish Karunakaran, Shravan Murlidaran
 * The code is available at https://github.com/HarishKarunakaran/Data_Structures/
 *
 */

#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <functional>
#include <data_structures/common/node.h>

class KdTree
{
    /**
         * \brief Root Node of the KdTree
         */
    std::shared_ptr<Node> data_;
    /**
         * \brief splitting axis of the data
         */
    unsigned int cutDimension_;
    /**
         * \brief dimension of the input data
         */
    unsigned int dataDimension_ = 2;

protected:
    /**
         * \brief insert Node into KdTree
         */
    template <typename T>
    std::shared_ptr<Node> insertNode(std::vector<T>& data,
                                            std::shared_ptr<Node> kd_node,
                                            unsigned int cd)
    {

        if(kd_node == nullptr) kd_node = std::make_shared<Node>(data, dataDimension_);

        else if(data == kd_node->getValues())
            return nullptr;

        else if(data.at(cd) < kd_node->getValue(cd))
            kd_node->setNode(insertNode(data, kd_node->getNode(0), (cd+1) % dataDimension_), 0);

        else
            kd_node->setNode(insertNode(data, kd_node->getNode(1), (cd+1) % dataDimension_), 1);

        return kd_node;
    }
    /**
         * \brief insert Node into KdTree
         */
    template <typename T>
    std::shared_ptr<Node> findNode(std::vector<T> data,
                                          std::shared_ptr<Node> kd_node,
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
    /**
         * \brief delete node from KdTree
         */
    template <typename T>
    std::shared_ptr<Node> deleteNode(std::vector<T> data,
                                            std::shared_ptr<Node> kd_node,
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
    /**
         * \brief Find Minimum along a specified axis
         */
    std::shared_ptr<Node> minNode(std::shared_ptr<Node> kd_node,
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
    /**
         * \brief Find Maximum along a specified axis
         */
    std::shared_ptr<Node> maxNode(std::shared_ptr<Node> kd_node,
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

    /**
         * \brief Compares three nodes along an axis and returns minimum
         */
    std::shared_ptr<Node> minimum(std::shared_ptr<Node> node1,
                                         std::shared_ptr<Node> node2,
                                         std::shared_ptr<Node> node3,
                                         unsigned int axis)
    {
        if(node1 == nullptr && node2 == nullptr)
            return node3;

        else if(node1 == nullptr){
            if(node2->getValue(axis) < node3->getValue(axis))
                return node2;
        }

        else if(node2 == nullptr)
                if(node1->getValue(axis) < node3->getValue(axis))
                    return node1;

        return node3;
    }
    /**
         * \brief Compares three nodes along an axis and returns maximum
         */
    std::shared_ptr<Node> maximum(std::shared_ptr<Node> node1,
                                         std::shared_ptr<Node> node2,
                                         std::shared_ptr<Node> node3,
                                         unsigned int axis)
    {
        if(node1 == nullptr && node2 == nullptr)
            return node3;

        else if(node1 == nullptr){
            if(node2->getValue(axis) > node3->getValue(axis))
                return node2;
        }

        else if(node2 == nullptr)
                if(node1->getValue(axis) > node3->getValue(axis))
                    return node1;

        return node3;
    }

    /**
         * \brief Visualize the Tree
         */
    void visualizeTree(std::shared_ptr<Node> node, unsigned int space)
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


public:
    /**
         * \brief Initiates a KdTree object
         */
    KdTree()
    {
        std::cout << "ctor - KdTree \n";
        data_ = nullptr;
        cutDimension_ = 0;
    }
    /**
         * \brief Initiates a KdTree object
         */
    KdTree(unsigned int cd) : cutDimension_(cd)
    {
        std::cout << "ctor - KdTree \n";
        data_ = nullptr;
    }
    /**
         * \brief Initiates a KdTree object
         */
    template <typename T>
    KdTree(std::vector<T>& data, unsigned int cd) : cutDimension_(cd), data_(std::make_shared<Node<T> >(data, data.size()))
    {
        std::cout << "ctor - KdTree \n";
    }
    /**
         * \brief Delete KdTree Object
         */
    ~KdTree();
    /**
         * \brief Create Tree structure for given input data
         */
    template <typename T>
    bool build(std::vector<std::vector<T> >& data)
    {
        for(auto& node_data : data)
            insert(node_data);

        return true;
    }
    /**
         * \brief Create Tree structure for given input data - rvalue
         */
    template <typename T>
    bool build(std::vector<std::vector<T> >&& data)
    {
        for(auto& node_data : data)
            insert(node_data);

        return true;
    }
    /**
         * \brief Helper function to insert node
         */
    template <typename T>
    bool insert(std::vector<T>& data)
    {

        if(data.empty()){
            std::cerr << "Empty point provided!!" << '\n';
            return false;
        }
        if(data_ == nullptr){
            data_ = std::make_shared<Node>(data, data.size());
            dataDimension_ = data.size();
            return true;
        }

        if(insertNode(data, data_, cutDimension_) == nullptr)
            return false;

        return true;
    }
    /**
         * \brief Helper function to insert node - rvalue
         */
    template <typename T>
    bool insert(std::vector<T>&& data)
    {
        if(data.empty()){
            std::cerr << "Empty point provided!!" << '\n';
            return false;
        }
        if(data_ == nullptr){
            data_ = std::make_shared<Node>(data, data.size());
            dataDimension_ = data.size();
            return true;
        }

        if(insertNode(data, data_, cutDimension_) == nullptr)
            return false;

        return true;
    }

    /**
         * \brief Helper function to find node
         */
    template <typename T>
    bool find(std::vector<T>& data)
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
    /**
         * \brief Helper function to find node - rvalue
         */
    template <typename T>
    bool find(std::vector<T>&& data)
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
    /**
         * \brief Helper function to delete node
         */
    template <typename T>
    bool erase(std::vector<T>& data)
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
    /**
         * \brief Helper function to delete node - rvalue
         */
    template <typename T>
    bool erase(std::vector<T>&& data)
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
    /**
         * \brief Helper function to find minimum along a specified axis
         */
    template <typename T>
    void min(std::vector<T>& minimum,
             unsigned int axis)
    {
        if(data_ == nullptr) return;
        minimum = (minNode(data_, axis, cutDimension_))->getValues();
    }
    /**
         * \brief Helper function to find maximum along a specified axis
         */
    template <typename T>
    void max(std::vector<T>& maximum,
                             unsigned int axis)
    {
        if(data_ == nullptr) return;
        maximum = (maxNode(data_, axis, cutDimension_))->getValues();
    }
    /**
         * \brief Helper function to visualize tree
         */
    void view()
    {
        visualizeTree(data_, 0);
    }
    /**
         * \brief Move Constructor
         */
    KdTree(KdTree&& ) noexcept = default;
    /**
         * \brief Copy Constructor
         */
    KdTree(const KdTree& kdtree) : data_(kdtree.data_)
    { std::cout << "copy - KdTree \n";}
    /**
         * \brief Copy Assingment Operator
         */
    KdTree& operator=(const KdTree& kdtree) noexcept
    {
        return *this = Kdtree(kdtree);
    }

    /**
         * \brief Move Assignment Operator
         */
    KdTree& operator=(KdTree&&) noexcept = default;

};

#endif // KDTREE_H
