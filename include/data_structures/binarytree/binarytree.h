/*
 * This code is developed to implement the Binarytree data structure
 * The authors of this code is Harish Karunakaran
 * The code is available at https://github.com/HarishKarunakaran/Data_Structures/
 *
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <functional>
#include <data_structures/common/node.h>

template <typename T>
class Binarytree
{
    /**
         * \brief Root Node of the Binarytree
         */
    std::shared_ptr<Node<T> > data_;

protected:
    /**
         * \brief insert Node into Binarytree
         */
    std::shared_ptr<Node<T> > insertNode(const std::vector<T>& data,
                                         std::shared_ptr<Node<T> > bin_node)
    {

        if(bin_node == nullptr) bin_node = std::make_shared<Node<T> >(data, 2);

        else if(data == bin_node->getValues())
            return nullptr;

        else if(data.at(0) < bin_node->getValue(0))
            bin_node->setNode(insertNode(data, bin_node->getNode(0)), 0);

        else
            bin_node->setNode(insertNode(data, bin_node->getNode(1)), 1);

        return bin_node;
    }
    /**
         * \brief insert Node into Binarytree
         */
    std::shared_ptr<Node<T> > findNode(std::vector<T> data,
                                          std::shared_ptr<Node<T> > bin_node)
    {
        if (bin_node == nullptr)
            return nullptr;

        if(data == bin_node->getValues())
            return bin_node;

        else if (data.at(0) < bin_node->getValue(0))
            bin_node = findNode(data, bin_node->getNode(0));

        else
            bin_node = findNode(data, bin_node->getNode(1));

        return bin_node;
    }
    /**
         * \brief delete node from Binarytree
         */
    std::shared_ptr<Node<T> > deleteNode(std::vector<T> data,
                                            std::shared_ptr<Node<T> > bin_node)
    {
        if (bin_node == nullptr)
            return nullptr;

        unsigned int axis = 0;
        unsigned int new_axis = (axis + 1) % 2;

        if(data == bin_node->getValues()){
            if(bin_node->getNode(1) != nullptr){
                auto min1 = minNode(bin_node->getNode(1), axis, new_axis)->getValues();
                bin_node->setValue(min1);
                bin_node->setNode(deleteNode(bin_node->getValues(), bin_node->getNode(1), new_axis), 1);
        }

            else if(bin_node->getNode(0) != nullptr){
                auto min0 = minNode(bin_node->getNode(0), axis, new_axis)->getValues();
                bin_node->setValue(min0);
                bin_node->setNode(deleteNode(bin_node->getValues(), bin_node->getNode(0), new_axis), 1);
        }
            else
                bin_node = nullptr;
        }
        else if (data.at(axis) < bin_node->getValue(axis))
            bin_node->setNode(deleteNode(data, bin_node->getNode(0), new_axis), 0);

        else
            bin_node->setNode(deleteNode(data, bin_node->getNode(1), new_axis), 1);

        return bin_node;
    }
    /**
         * \brief Find Minimum along a specified axis
         */
    std::shared_ptr<Node<T> > minNode(std::shared_ptr<Node<T> > bin_node,
                                         unsigned int axis,
                                         unsigned int cd)
    {
        if (bin_node == nullptr)
            return nullptr;

        if (cd == axis)
        {
            if (bin_node->getNode(0) == nullptr)
                return bin_node;

            return minNode(bin_node->getNode(0));
        }

        else
            return minimum(minNode(bin_node->getNode(0)),
                           minNode(bin_node->getNode(1)),
                           bin_node,
                           axis);
    }
    /**
         * \brief Find Maximum along a specified axis
         */
    std::shared_ptr<Node<T> > maxNode(std::shared_ptr<Node<T> > bin_node,
                                         unsigned int axis,
                                         unsigned int cd)
    {
        if (bin_node == nullptr)
            return nullptr;

        if (cd == axis)
        {
            if (bin_node->getNode(0) == nullptr)
                return bin_node;

            return maxNode(bin_node->getNode(0));
        }

        else
            return maximum(maxNode(bin_node->getNode(0), axis),
                           maxNode(bin_node->getNode(1), axis),
                           bin_node,
                           axis);
    }

    /**
         * \brief Compares three nodes along an axis and returns minimum
         */
    std::shared_ptr<Node<T> > minimum(std::shared_ptr<Node<T> > node1,
                                         std::shared_ptr<Node<T> > node2,
                                         std::shared_ptr<Node<T> > node3,
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
    std::shared_ptr<Node<T> > maximum(std::shared_ptr<Node<T> > node1,
                                         std::shared_ptr<Node<T> > node2,
                                         std::shared_ptr<Node<T> > node3,
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
    void visualizeTree(std::shared_ptr<Node<T> > node, unsigned int space)
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
         * \brief Initiates a Binarytree object
         */
    Binarytree()
    {
        std::cout << "ctor - Binarytree \n";
        data_ = nullptr;
    }
    /**
         * \brief Initiates a Binarytree object
         */
    Binarytree(const std::vector<T>& data) : data_(std::make_shared<Node<T> >(data, 2))
    {
        std::cout << "ctor - Binarytree \n";
    }
    /**
         * \brief Delete Binarytree Object
         */
    ~Binarytree()
    {

    }

    /**
         * \brief Create Tree structure for given input data
         */
    template <
        class UR = std::vector<std::vector<T> >,
        class TypeMustBeStdVectorofVectors = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<std::vector<T> > >::value>
    >
    bool build(UR&& data)
    {
        for(auto& node_data : data)
        {
            if(!insert(node_data))
                return false;
        }
        return true;
    }
    /**
         * \brief Helper function to insert node
         */
    template <
        class UR = std::vector<T>,
        class TypeMustBeStdVector = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<T> >::value>
    >
    bool insert(const UR&& data)
    {

        if(data.empty()){
            std::cerr << "Empty point provided!!" << '\n';
            return false;
        }
        if(data_ == nullptr){
            data_ = std::make_shared<Node<T> >(data, 2);
            return true;
        }

        if(insertNode(data, data_) == nullptr)
            return false;

        return true;
    }
    /**
         * \brief Helper function to find node
         */
    template <
        class UR = std::vector<T> ,
        class TypeMustBeStdVector = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<T> >::value>
    >
    bool find(UR&& data)
    {
        if(data_ == nullptr){
            std::cerr << "Sorry, Tree not built yet!!" << '\n';
            return false;
        }

        if(data.empty()){
            std::cerr << "Empty point provided!!" << '\n';
            return false;
        }

        if(findNode(data, data_) == nullptr){
            std::cout << "Point not found" << '\n';
            return false;
        }

        return true;
    }
    /**
         * \brief Helper function to delete node
         */
    template <
        class UR = std::vector<T>,
        class TypeMustBeStdVector = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<T> >::value>
    >
    bool erase(UR&& data)
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

        else if(deleteNode(data, data_) == nullptr){
            std::cout << "Point not found" << '\n';
            return false;
        }

        return true;
    }
    /**
         * \brief Helper function to find minimum along a specified axis
         */
    void min(std::vector<T>& minimum,
             unsigned int axis)
    {
        if(data_ == nullptr) return;
        minimum = (minNode(data_))->getValues();
    }
    /**
         * \brief Helper function to find maximum along a specified axis
         */
    void max(std::vector<T>& maximum,
                             unsigned int axis)
    {
        if(data_ == nullptr) return;
        maximum = (maxNode(data_))->getValues();
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
    Binarytree(Binarytree&& ) noexcept = default;
    /**
         * \brief Copy Constructor
         */
    Binarytree(const Binarytree& Binarytree) : data_(Binarytree.data_)
    { std::cout << "copy - Binarytree \n";}
    /**
         * \brief Copy Assingment Operator
         */
    Binarytree& operator=(const Binarytree& Binarytree) noexcept
    {
        return *this = Binarytree(Binarytree);
    }

    /**
         * \brief Move Assignment Operator
         */
    Binarytree& operator=(Binarytree&&) noexcept = default;

};

#endif // BINARYTREE_H
