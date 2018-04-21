/** @file kdtree.h
 *  @brief KdTree Class
 *
 *  This contains the definitions and helper functions for Binary Search Tree class
 *
 *  @author Harish Karunakaran
 *  @bug No known bugs.
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <functional>
#include <type_traits>
#include <data_structures/common/node.h>

template <typename T>
class Binarytree
{
    /**
         * \brief Root Node of the Binarytree
         */
    std::shared_ptr<Node<T> > root_;

protected:
    /**
         * \brief insert Node into Binarytree
         */
    std::shared_ptr<Node<T> > insertNode(const T& data,
                                         std::shared_ptr<Node<T> > bin_node) const
    {

        if(bin_node == nullptr) bin_node = std::make_shared<Node<T> >(data, 2);

        else if(data == bin_node->getValue())
            return nullptr;

        else if(data < bin_node->getValue())
            bin_node->setNode(insertNode(data, bin_node->getNode(0)), 0);

        else
            bin_node->setNode(insertNode(data, bin_node->getNode(1)), 1);

        return bin_node;
    }
    /**
         * \brief insert Node into Binarytree
         */
    std::shared_ptr<Node<T> > findNode(const T& data,
                                       std::shared_ptr<Node<T> > bin_node) const
    {
        if (bin_node == nullptr)
            return nullptr;

        if(data == bin_node->getValue())
            return bin_node;

        else if (data < bin_node->getValue())
            bin_node = findNode(data, bin_node->getNode(0));

        else
            bin_node = findNode(data, bin_node->getNode(1));

        return bin_node;
    }
    /**
         * \brief delete node from Binarytree
         */
    std::shared_ptr<Node<T> > deleteNode(const T& data,
                                         std::shared_ptr<Node<T> > bin_node) const
    {
        if (bin_node == nullptr)
            return nullptr;

        if(data == bin_node->getValue())
        {
            if(bin_node->getNode(1) != nullptr)
            {
                auto min1 = minNode(bin_node->getNode(1))->getValue();
                bin_node->setValue(min1);
                bin_node->setNode(deleteNode(bin_node->getValue(), bin_node->getNode(1)), 1);
            }

            else
                bin_node = nullptr;
        }

        else if (data < bin_node->getValue())
        {
            bin_node->setNode(deleteNode(data, bin_node->getNode(0)), 0);
        }

        else
            bin_node->setNode(deleteNode(data, bin_node->getNode(1)), 1);

        return bin_node;
    }
    /**
         * \brief Find Minimum along a specified axis
         */
    std::shared_ptr<Node<T> > minNode(std::shared_ptr<Node<T> > bin_node) const
    {
        if (bin_node == nullptr)
            return nullptr;

        if (bin_node->getNode(0) == nullptr)
            return bin_node;

        return minNode(bin_node->getNode(0));
    }
    /**
         * \brief Find Maximum along a specified axis
         */
    std::shared_ptr<Node<T> > maxNode(std::shared_ptr<Node<T> > bin_node) const
    {
        if (bin_node == nullptr)
            return nullptr;

        if (bin_node->getNode(1) == nullptr)
            return bin_node;

        return maxNode(bin_node->getNode(1));
    }

    /**
         * \brief Visualize the Tree
         */
    void visualizeTree(std::shared_ptr<Node<T> > node, unsigned int space) const
    {
        if(node == nullptr)
            return;
        space += 10;

        visualizeTree(node->getNode(1), space);
        std::cout << '\n';

        for(unsigned int i = 10; i < space; ++i)
            std::cout << " ";

        std::cout << node->getValue() << " ";

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
        root_ = nullptr;
    }
    /**
         * \brief Initiates a Binarytree object
         */
    Binarytree(const T& data) : root_(std::make_shared<Node<T> >(data, 2))
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
        class UR = std::vector<T>,
        class TypeMustBeStdVectorofVectors = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<T> >::value>
    >
    bool build(UR&& data)
    {
        for(auto& node_data : data)
        {
            if(!insert(std::forward<const T>(node_data)))
                return false;
        }
        return true;
    }
    /**
         * \brief Helper function to insert node
         */
    template <
        class UR = T,
        class TypeMustT = std::remove_reference_t<UR>
    >
    bool insert(const UR&& data)
    {
        static_assert((std::is_same<UR, T>::value),
                          "The data-type of class does not match with the argument");

        if(root_ == nullptr){
            root_ = std::make_shared<Node<T> >(data, 2);
            return true;
        }

        if(insertNode(data, root_) == nullptr)
            return false;

        return true;
    }
    /**
         * \brief Helper function to find node
         */
    template <
        class UR = T,
        class TypeMustBeT = std::remove_reference_t<UR>
    >
    bool find(const UR&& data) const
    {
        static_assert((std::is_same<UR, T>::value),
                          "The data-type of class does not match with the argument");

        if(root_ == nullptr){
            std::cerr << "Sorry, Tree not built yet!!" << '\n';
            return false;
        }

        if(findNode(data, root_) == nullptr){
            std::cout << "Point not found" << '\n';
            return false;
        }

        return true;
    }
    /**
         * \brief Helper function to delete node
         */
    template <
        class UR = T,
        class TypeMustBeT = std::remove_reference_t<UR>
    >
    bool erase(const UR&& data)
    {
        static_assert((std::is_same<UR, T>::value),
                          "The data-type of class does not match with the argument");

        if(root_ == nullptr){
            std::cerr << "Sorry, Tree not built yet!!" << '\n';
            return false;
        }

        if((root_->getNode(0) == nullptr) && (root_->getNode(1) == nullptr))
            root_ = nullptr;

        else if(deleteNode(data, root_) == nullptr){
            std::cout << "Point not found" << '\n';
            return false;
        }

        return true;
    }
    /**
         * \brief Helper function to find minimum along a specified axis
         */
    void min(T& minimum) const
    {
        if(root_ == nullptr) return;
        minimum = (minNode(root_))->getValue();
    }
    /**
         * \brief Helper function to find maximum along a specified axis
         */
    void max(T& maximum) const
    {
        if(root_ == nullptr) return;
        maximum = (maxNode(root_))->getValue();
    }
    /**
         * \brief Helper function to visualize tree
         */
    void view() const
    {
        visualizeTree(root_, 0);
    }
    /**
         * \brief Move Constructor
         */
    Binarytree(Binarytree&& ) noexcept = default;
    /**
         * \brief Copy Constructor
         */
    Binarytree(const Binarytree& Binarytree) : root_(Binarytree.root_)
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
