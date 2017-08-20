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
    int cutDimension_;
    /**
         * \brief dimension of the input data
         */
    int dataDimension_ = 2;

protected:
    /**
         * \brief insert Node into KdTree
         */
    std::shared_ptr<Node<T> > insertNode(std::vector<T>& , std::shared_ptr<Node<T> >, int);
    /**
         * \brief delete node from KdTree
         */
    std::vector<T> deleteNode(std::vector<T>& , std::shared_ptr<Node<T> >, int);
    /**
         * \brief Find Minimum along a specified axis
         */
    std::vector<T> minNode(std::shared_ptr<Node<T> >, int, int);
    /**
         * \brief Find Maximum along a specified axis
         */
    std::vector<T> maxNode(std::shared_ptr<Node<T> >, int, int);


public:
    /**
         * \brief Initiates a KdTree object
         */
    KdTree(int cutDimension_ = 0);
    /**
         * \brief Initiates a KdTree object
         */
    KdTree(std::vector<T>, int cutDimension_ = 0);
    /**
         * \brief Delete KdTree Object
         */
    ~KdTree();
    /**
         * \brief Create Tree structure for given input data
         */
    bool buildTree(std::vector<std::vector<T> >& );
    /**
         * \brief Helper function to insert node
         */
    bool insert_node(std::vector<T>& );
    /**
         * \brief Helper function to delete node
         */
    bool delete_node(std::vector<T>& );
    /**
         * \brief Helper function to find minimum along a specified axis
         */
    void find_min(std::vector<T>&, int);
    /**
         * \brief Helper function to find maximum along a specified axis
         */
    void find_max(std::vector<T>&, int);

    std::vector<T> minimum(std::vector<T>, std::vector<T>, std::vector<T>, int);

    std::vector<T> maximum(std::vector<T>, std::vector<T>, std::vector<T>, int);


};

//template class KdTree<int>;
//template class KdTree<float>;
//template class KdTree<double>;

//#include "kdtree/kdtree.cpp"

#endif // KDTREE_H
