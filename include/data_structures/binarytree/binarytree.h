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
    std::shared_ptr<Node<T> > root_;

protected:
    /**
         * \brief insert Node into Binarytree
         */
    std::shared_ptr<Node<T> > insertNode(const std::vector<T>& data,
                                         std::shared_ptr<Node<T> > bin_node) const
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
    std::shared_ptr<Node<T> > findNode(const std::vector<T>& data,
                                       std::shared_ptr<Node<T> > bin_node) const
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

    // Have to fix
    std::shared_ptr<Node<T> > deleteNode(const std::vector<T>& data,
                                         std::shared_ptr<Node<T> > bin_node) const
    {
        if (bin_node == nullptr)
            return nullptr;

        if(data == bin_node->getValues())
        {
            if(bin_node->getNode(1) != nullptr)
            {
                                                std::cout << "yes" << '\n';
                auto min1 = minNode(bin_node->getNode(1))->getValues();
                bin_node->setValue(min1);
                bin_node->setNode(deleteNode(bin_node->getValues(), bin_node->getNode(1)), 1);
            }

            else
                bin_node = nullptr;
        }

        else if (data < bin_node->getValues())
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
        root_ = nullptr;
    }
    /**
         * \brief Initiates a Binarytree object
         */
    Binarytree(const std::vector<T>& data) : root_(std::make_shared<Node<T> >(data, 2))
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
            if(!insert(std::forward<const std::vector<T> >(node_data)))
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
        class UR = std::vector<T> ,
        class TypeMustBeStdVector = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<T> >::value>
    >
    bool find(const UR&& data) const
    {
        if(root_ == nullptr){
            std::cerr << "Sorry, Tree not built yet!!" << '\n';
            return false;
        }

        if(data.empty()){
            std::cerr << "Empty point provided!!" << '\n';
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
        class UR = std::vector<T>,
        class TypeMustBeStdVector = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<T> >::value>
    >
    bool erase(const UR&& data)
    {
        if(root_ == nullptr){
            std::cerr << "Sorry, Tree not built yet!!" << '\n';
            return false;
        }

        if(data.empty()){
            std::cerr << "Empty point provided!!" << '\n';
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
    void min(std::vector<T>& minimum) const
    {
        if(root_ == nullptr) return;
        minimum = (minNode(root_))->getValues();
    }
    /**
         * \brief Helper function to find maximum along a specified axis
         */
    void max(std::vector<T>& maximum) const
    {
        if(root_ == nullptr) return;
        maximum = (maxNode(root_))->getValues();
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
