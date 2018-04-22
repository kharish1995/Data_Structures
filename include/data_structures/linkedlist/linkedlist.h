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
    std::shared_ptr<Node<T> > insertNode(const T& data,
                                         std::shared_ptr<Node<T> > ll_node) const
    {
        if(ll_node == nullptr) ll_node = std::make_shared<Node<T> >(data, 1);

        else    ll_node->setNode(insertNode(data, ll_node->getNode(0)), 0);

        return ll_node;
    }

    /**
         * \brief insert Node into Linkedlist
         */
    std::shared_ptr<Node<T> > findNode(const T& data,
                                       std::shared_ptr<Node<T> > ll_node) const
    {

    }
    /**
         * \brief delete node from Linkedlist
         */
    std::shared_ptr<Node<T> > deleteNode(const T& data,
                                         std::shared_ptr<Node<T> > ll_node)
    {
        if (ll_node == nullptr)
            return nullptr;

        if(data == ll_node->getValue())
        {
            if(ll_node->getNode(0) != nullptr)
            {
                //auto min1 = minNode(ll_node->getNode(0))->getValues();
                ll_node->setValue(0);
                ll_node->setNode(deleteNode(ll_node->getValue(), ll_node->getNode(0)), 0);
            }
            else
                ll_node = nullptr;
        }

        else
            ll_node->setNode(deleteNode(data, ll_node->getNode(0)), 0);

        return ll_node;
    }

    /**
         * \brief Visualize the Tree
         */
    void visualize(std::shared_ptr<Node<T> > data) const
    {

        if(data == nullptr)
            return;

        std::cout << data << "-> ";
        visualize(data->getNode(0));
        std::cout << "\n";
    }


public:
    /**
         * \brief Initiates a Linkedlist object
         */
    Linkedlist() : data_(nullptr) { }
    /**
       * \brief Initiates a Linkedlist object
       */
    Linkedlist(T& data) : data_(std::make_shared<Node<T> >(data, 1)) { }
    /**
         * \brief Delete Linkedlist Object
         */
    ~Linkedlist() { }
    /**
         * \brief Helper function to insert node
         */
    template <
        class UR = T,
        class TypeMustBeT = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, T>::value>
    >
    bool insert(UR&& data)
    {
        if(data_ == nullptr){
            data_ = std::make_shared<Node<T> >(data, 1);
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
        class UR = T,
        class TypeMustBeT = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, T >::value>
    >
    bool find(UR&& data) const
    {
        return true;
    }
    /**
         * \brief Helper function to delete node
         */
    template <
        class UR = T,
        class TypeMustBeT = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, T >::value>
    >
    bool erase(UR&& data)
    {
        if(data_ == nullptr){
            std::cerr << "Sorry, Linked List not built yet!!" << '\n';
            return false;
        }

        if(data_->getNode(0) == nullptr)
            data_ = nullptr;

        else if(deleteNode(data, data_) == nullptr){
            std::cout << "Point not found" << '\n';
            return false;
        }

        return true;
    }

    /**
         * \brief Helper function to visualize Linked List
         */
    void view() const
    {
        visualize(data_);
    }
    /**
         * \brief Move Constructor
         */
    Linkedlist(Linkedlist&& ) noexcept = default;
    /**
         * \brief Copy Constructor
         */
    Linkedlist(const Linkedlist& linked_list) : data_(linked_list.data_)
    {

    }

    /**
         * \brief Copy Assingment Operator
         */
    Linkedlist& operator=(const Linkedlist& linked_list) noexcept
    {
        return *this = Linkedlist(linked_list);
    }
    /**
         * \brief Move Assignment Operator
         */
    Linkedlist& operator=(Linkedlist&&) noexcept = default;

};

#endif // Linkedlist_H
