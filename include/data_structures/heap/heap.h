/*
 * This code is developed to implement the heap data structure
 * The authors of this code are Harish Karunakaran
 * The code is available at https://github.com/HarishKarunakaran/Data_Structures/
 *
 */

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <functional>
#include <data_structures/common/node.h>

template <typename T>
class Heap
{
    /**
         * \brief Elements of the Heap
         */
    std::vector<T> data_;
    /**
         * \brief Current size of the Heap
         */
    size_t size_;
    /**
         * \brief Max size of heap
         */
    size_t max_size_;

protected:
    /**
         * \brief insert Node into Heap
         */
    std::shared_ptr<Node<T> > insertNode(const std::vector<T>& data,
                                         std::shared_ptr<Node<T> > heap_node) const
    {

        if(heap_node == nullptr) heap_node = std::make_shared<Node<T> >(data, 2);

        else if(data == heap_node->getValues())
            return nullptr;

        else if(data.at(cd) < heap_node->getValue(cd))
            heap_node->setNode(insertNode(data, heap_node->getNode(0)), 0);

        else
            heap_node->setNode(insertNode(data, heap_node->getNode(1)), 1);

        return heap_node;
    }
    /**
         * \brief insert Node into Heap
         */
    std::shared_ptr<Node<T> > findNode(const std::vector<T>& data,
                                       std::shared_ptr<Node<T> > heap_node) const
    {
        if (heap_node == nullptr)
            return nullptr;

        if(data == heap_node->getValues())
            return heap_node;

        else if (data.at(axis) < heap_node->getValue(axis))
            heap_node = findNode(data, heap_node->getNode(0));

        else
            heap_node = findNode(data, heap_node->getNode(1));

        return heap_node;
    }
    /**
         * \brief delete node from Heap
         */
    std::shared_ptr<Node<T> > deleteNode(const std::vector<T>& data,
                                         std::shared_ptr<Node<T> > heap_node) const
    {
        if (heap_node == nullptr)
            return nullptr;

        if(data == heap_node->getValues()){
            if(heap_node->getNode(1) != nullptr){
                auto min1 = minNode(heap_node->getNode(1), axis, new_axis)->getValues();
                heap_node->setValue(min1);
                heap_node->setNode(deleteNode(heap_node->getValues(), heap_node->getNode(1), new_axis), 1);
        }

            else if(heap_node->getNode(0) != nullptr){
                auto min0 = minNode(heap_node->getNode(0), axis, new_axis)->getValues();
                heap_node->setValue(min0);
                heap_node->setNode(deleteNode(heap_node->getValues(), heap_node->getNode(0), new_axis), 1);
        }
            else
                heap_node = nullptr;
        }
        else if (data.at(axis) < heap_node->getValue(axis))
            heap_node->setNode(deleteNode(data, heap_node->getNode(0), new_axis), 0);

        else
            heap_node->setNode(deleteNode(data, heap_node->getNode(1), new_axis), 1);

        return heap_node;
    }
    /**
         * \brief Find Minimum along a specified axis
         */
    std::shared_ptr<Node<T> > minNode(std::shared_ptr<Node<T> > heap_node) const
    {
        if (heap_node == nullptr)
            return nullptr;

        if (cd == axis)
        {
            if (heap_node->getNode(0) == nullptr)
                return heap_node;

            return minNode(heap_node->getNode(0));
        }

        else
            return minimum(minNode(heap_node->getNode(0)),
                           minNode(heap_node->getNode(1)),
                           heap_node);
    }
    /**
         * \brief Find Maximum along a specified axis
         */
    std::shared_ptr<Node<T> > maxNode(std::shared_ptr<Node<T> > heap_node) const
    {
        if (heap_node == nullptr)
            return nullptr;

        if (cd == axis)
        {
            if (heap_node->getNode(0) == nullptr)
                return heap_node;

            return maxNode(heap_node->getNode(0));
        }

        else
            return maximum(maxNode(heap_node->getNode(0)),
                           maxNode(heap_node->getNode(1)),
                           heap_node);
    }

    /**
         * \brief Compares three nodes along an axis and returns minimum
         */
    std::shared_ptr<Node<T> > minimum(std::shared_ptr<Node<T> > node1,
                                      std::shared_ptr<Node<T> > node2,
                                      std::shared_ptr<Node<T> > node3) const
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
                                      std::shared_ptr<Node<T> > node3) const
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
    void visualizeTree(std::shared_ptr<Node<T> > node,
                       unsigned int space) const
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
         * \brief Initiates a Heap object
         */
    Heap(size_t maxsize) : max_size_(maxsize)
    {
        std::cout << "ctor - Heap \n";
        size_ = 0;
        data_.capacity(max_size_);
    }
    /**
         * \brief Initiates a Heap object
         */
    Heap(const std::vector<T>& data, size_t maxsize) : data_(std::make_shared<Node<T> >(data, 2))
    {
        std::cout << "ctor - Heap \n";
    }
    /**
         * \brief Delete Heap Object
         */
    ~Heap()
    {

    }

    /**
         * \brief Create Tree structure for given input data
         */
    template <
        class UR = std::vector<std::vector<T> >,
        class TypeMustBeStdVectorofVectors = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<std::vector<T> > >::value>
    >
    bool build(const UR&& data)
    {
        for(const auto& node_data : data)
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
    Heap(Heap&& ) noexcept = default;
    /**
         * \brief Copy Constructor
         */
    Heap(const Heap& Heap) : root_(Heap.root_)
    { std::cout << "copy - Heap \n";}
    /**
         * \brief Copy Assingment Operator
         */
    Heap& operator=(const Heap& heap) noexcept
    {
        return *this = Heap(heap);
    }

    /**
         * \brief Move Assignment Operator
         */
    Heap& operator=(Heap&&) noexcept = default;

};

#endif // Heap_H
