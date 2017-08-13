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
    int dataDimension_;

protected:
    /**
         * \brief insert Node into KdTree
         */
    bool insert(std::vector<T>& , std::shared_ptr<Node<T> >, int);
    /**
         * \brief delete node from KdTree
         */
    std::vector<T>& delete_node(std::vector<T>& , std::shared_ptr<Node<T> >, int);
    /**
         * \brief Find Minimum along a specified axis
         */
    std::vector<T>& min(std::shared_ptr<Node<T> >, int, int);
    /**
         * \brief Find Maximum along a specified axis
         */
    std::vector<T>& max(std::shared_ptr<Node<T> >, int, int);


public:
    /**
         * \brief Initiates a KdTree object
         */
    KdTree(int cutDimension_ = 0);
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
    bool insertNode(std::vector<T>& );
    /**
         * \brief Helper function to delete node
         */
    bool deleteNode(std::vector<T>& );
    /**
         * \brief Helper function to find minimum along a specified axis
         */
    void findMin(std::vector<T>&, int);
    /**
         * \brief Helper function to find maximum along a specified axis
         */
    void findMax(std::vector<T>&, int);

};

#endif // KDTREE_H
