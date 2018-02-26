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

template <typename T>
class KdTree
{
    /**
         * \brief Root Node of the KdTree
         */
    std::shared_ptr<Node<T> > data_;
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
    std::shared_ptr<Node<T> > insertNode(std::vector<T>& , std::shared_ptr<Node<T> >, unsigned int);
    /**
         * \brief insert Node into KdTree
         */
    std::shared_ptr<Node<T> > findNode(std::vector<T> , std::shared_ptr<Node<T> > , unsigned int );
    /**
         * \brief delete node from KdTree
         */
    std::shared_ptr<Node<T> > deleteNode(std::vector<T> , std::shared_ptr<Node<T> > , unsigned int);
    /**
         * \brief Find Minimum along a specified axis
         */
    std::shared_ptr<Node<T> > minNode(std::shared_ptr<Node<T> >, unsigned int, unsigned int);
    /**
         * \brief Find Maximum along a specified axis
         */
    std::shared_ptr<Node<T> > maxNode(std::shared_ptr<Node<T> >, unsigned int, unsigned int);
    /**
         * \brief Compares three nodes along an axis and returns minimum
         */
    std::shared_ptr<Node<T> > minimum(std::shared_ptr<Node<T> >, std::shared_ptr<Node<T> >, std::shared_ptr<Node<T> >, unsigned int);
    /**
         * \brief Compares three nodes along an axis and returns maximum
         */
    std::shared_ptr<Node<T> > maximum(std::shared_ptr<Node<T> >, std::shared_ptr<Node<T> >, std::shared_ptr<Node<T> >, unsigned int);
    /**
         * \brief Visualize the Tree
         */
    void visualizeTree(std::shared_ptr<Node<T> > node, int space);


public:
    /**
         * \brief Initiates a KdTree object
         */
    KdTree();
    /**
         * \brief Initiates a KdTree object
         */
    KdTree(unsigned int cutDimension_);
    /**
         * \brief Initiates a KdTree object
         */
    KdTree(std::vector<T>& , unsigned int cutDimension_ = 0);
    /**
         * \brief Delete KdTree Object
         */
    ~KdTree();
    /**
         * \brief Create Tree structure for given input data
         */
    bool build(std::vector<std::vector<T> >&);
    /**
         * \brief Helper function to insert node
         */
    bool insert(std::vector<T>& );
    /**
         * \brief Helper function to insert node
         */
    bool find(std::vector<T>& );
    /**
         * \brief Helper function to delete node
         */
    bool erase(std::vector<T>& );
    /**
         * \brief Helper function to find minimum along a specified axis
         */
    void min(std::vector<T>&, unsigned int);
    /**
         * \brief Helper function to find maximum along a specified axis
         */
    void max(std::vector<T>&, unsigned int);
    /**
         * \brief Helper function to visualize tree
         */
    void view();
    /**
         * \brief Move Constructor
         */
    KdTree(KdTree&& ) = default;
    /**
         * \brief Copy Constructor
         */
    KdTree(const KdTree&) = default;
    /**
         * \brief Copy Assingment Operator
         */
    KdTree& operator=(const KdTree&) = default;
    /**
         * \brief Move Assignment Operator
         */
    KdTree& operator=(KdTree&&) = default;

};

#endif // KDTREE_H
