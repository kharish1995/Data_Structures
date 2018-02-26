/*
 * This code is developed to implement the Linked List data structure
 * The author of this code is Harish Karunakaran
 * The code is available at https://github.com/HarishKarunakaran/Data_Structures/
 *
 */

#ifndef Linkedlist_H
#define Linkedlist_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <functional>
#include <data_structures/common/node.h>

template <typename T>
class Linkedlist
{
    /**
         * \brief Root Node of the Linkedlist
         */
    std::shared_ptr<Node<T> > data_;

protected:
    /**
         * \brief insert Node into Linkedlist
         */
    std::shared_ptr<Node<T> > insertNode(std::vector<T>& , std::shared_ptr<Node<T> >, unsigned int);
    /**
         * \brief insert Node into Linkedlist
         */
    std::shared_ptr<Node<T> > findNode(std::vector<T> , std::shared_ptr<Node<T> > , unsigned int );
    /**
         * \brief delete node from Linkedlist
         */
    std::shared_ptr<Node<T> > deleteNode(std::vector<T> , std::shared_ptr<Node<T> > , unsigned int);
    /**
         * \brief Visualize the Tree
         */
    void visualize(std::shared_ptr<Node<T> > , unsigned int);


public:
    /**
         * \brief Initiates a Linkedlist object
         */
    Linkedlist();
    /**
         * \brief Delete Linkedlist Object
         */
    ~Linkedlist();
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
    Linkedlist(Linkedlist&& ) = default;
    /**
         * \brief Copy Constructor
         */
    Linkedlist(const Linkedlist&) = default;
    /**
         * \brief Copy Assingment Operator
         */
    Linkedlist& operator=(const Linkedlist&) = default;
    /**
         * \brief Move Assignment Operator
         */
    Linkedlist& operator=(Linkedlist&&) = default;

};

#endif // Linkedlist_H
