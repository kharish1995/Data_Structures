/*
 * This code is developed to implement the Binary Tree data structure
 * The author of this code is Harish Karunakaran
 * The code is available at https://github.com/HarishKarunakaran/Data_Structures/
 *
 */

#ifndef Binarytree_H
#define Binarytree_H

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
    std::shared_ptr<Node<T> > insertNode(std::vector<T>& , std::shared_ptr<Node<T> >, unsigned int);
    /**
         * \brief insert Node into Binarytree
         */
    std::shared_ptr<Node<T> > findNode(std::vector<T> , std::shared_ptr<Node<T> > , unsigned int );
    /**
         * \brief delete node from Binarytree
         */
    std::shared_ptr<Node<T> > deleteNode(std::vector<T> , std::shared_ptr<Node<T> > , unsigned int);
    /**
         * \brief Visualize the Tree
         */
    void visualize(std::shared_ptr<Node<T> > , unsigned int);


public:
    /**
         * \brief Initiates a Binarytree object
         */
    Binarytree();
    /**
         * \brief Delete Binarytree Object
         */
    ~Binarytree();
    /**
         * \brief Helper function to insert node
         */
    bool insert(std::vector<T>& );
    /**
         * \brief Helper function to insert node - rvalue
         */
    bool insert(std::vector<T>&& );
    /**
         * \brief Helper function to find node
         */
    bool find(std::vector<T>& );
    /**
         * \brief Helper function to find node - rvalue
         */
    bool find(std::vector<T>&& );
    /**
         * \brief Helper function to delete node
         */
    bool erase(std::vector<T>& );
    /**
         * \brief Helper function to delete node - rvalue
         */
    bool erase(std::vector<T>&& );
    /**
         * \brief Helper function to visualize tree
         */
    void view();
    /**
         * \brief Move Constructor
         */
    Binarytree(Binarytree&& ) = default;
    /**
         * \brief Copy Constructor
         */
    Binarytree(const Binarytree&) = default;
    /**
         * \brief Copy Assingment Operator
         */
    Binarytree& operator=(const Binarytree&) = default;
    /**
         * \brief Move Assignment Operator
         */
    Binarytree& operator=(Binarytree&&) = default;

};

#endif // Binarytree_H
