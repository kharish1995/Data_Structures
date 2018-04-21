#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
template <typename T>           //template parameter declaration
class Node
{
    /**
         * \brief stores the data in the node
         */
    T value_;
    /**
         * \brief pointers to children nodes
         */
    std::vector<std::shared_ptr<Node<T> > > nodes_;

public:
    /**
         * \brief Set the values of the Node
         */
    template <
        class UR = T,
        class TypeMustBeT = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, T>::value>
    >
    void setValue(UR&& value)
    {
        value_ = value;
    }
    /**
         * \brief Set the pointer to the Node
         */
    void setNode(const std::shared_ptr<Node<T> > node, unsigned int i)
    {
        if (i <= nodes_.size())
        {
            nodes_.at(i) = node;
            return;
        }
        std::cerr << "Index out of bounds for Node - setNode" << '\n';
    }
    /**
         * \brief constructs node object with the value given value
         */
    Node(const T& value, unsigned int size = 2) : nodes_(size, nullptr)
    {
        value_ = value;
    }
    /**
         * \brief constructs node object with the value given pointer to value
         */
    Node(const T* value, unsigned int size = 2): nodes_(size, nullptr)
    {
        value_ = *value;
    }
    /**
         * \brief deletes Node object
         */
    ~Node()
    {

    }
    /**
         * \brief get the value of a node
         */
    T getValue() const
    {
        return value_;
    }
    /**
         * \brief get one of the children of the node
         */
    std::shared_ptr<Node<T> > getNode(unsigned int i) const
    {
        try{
            return nodes_.at(i);
        }
          catch (const std::out_of_range& e){
            std::cerr << "Index Out of bounds for Node - getNode " << e.what() << '\n';
        }

        return nullptr;
    }
    /**
         * \brief Move Constructor
         */
    Node(Node&& ) = default;
    /**
         * \brief Copy Constructor
         */
    Node(const Node&) = default;
    /**
         * \brief Copy Assignment Operator
         */
    Node& operator=(const Node&) = default;
    /**
         * \brief Move Assingnment Operator
         */
    Node& operator=(Node&&) = default;

};

// Template Specialization for vector of data
template <>
template <typename U>
class Node<std::vector<U> >
{
    /**
         * \brief stores the data in the node
         */
    std::vector<U> value_;
    /**
         * \brief pointers to children nodes
         */
    std::vector<std::shared_ptr<Node<std::vector<U> > > > nodes_;

public:
    /**
         * \brief Set the values of the Node
         */
    template <
        class UR = std::vector<U>,
        class TypeMustBeStdVector = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<U> >::value>
    >
    void setValue(const UR&& value)
    {
        value_ = value;
    }
    /**
         * \brief Set the pointer to the Node
         */
    void setNode(const std::shared_ptr<Node<std::vector<U> > > node, unsigned int i)
    {
        if (i <= nodes_.size())
        {
            nodes_.at(i) = node;
            return;
        }
        std::cerr << "Index out of bounds for Node - setNode" << '\n';
    }
    /**
         * \brief constructs node object with the value given value
         */
    Node(const std::vector<U>& value, unsigned int size = 2) : nodes_(size, nullptr)
    {
        value_ = value;
    }
    /**
         * \brief constructs node object with the value given pointer to value
         */
    Node(const std::vector<U>* value, unsigned int size = 2): nodes_(size, nullptr)
    {
        value_ = *value;
    }
    /**
         * \brief deletes Node object
         */
    ~Node()
    {

    }

    /**
         * \brief get the value of a particular dimension
         */
    U getValue(unsigned int i) const
    {
        try{
            return value_.at(i);
        }
          catch (const std::out_of_range& e){
            std::cerr << "Index Out of bounds at Node - getValue " << e.what() << '\n';
        }

        return false;
    }

    /**
         * \brief get the entire node value
         */
    std::vector<U> getValues() const
    {
        return value_;
    }
    /**
         * \brief get one of the children of the node
         */
    std::shared_ptr<Node<std::vector<U> > > getNode(unsigned int i) const
    {
        try{
            return nodes_.at(i);
        }
          catch (const std::out_of_range& e){
            std::cerr << "Index Out of bounds for Node - getNode " << e.what() << '\n';
        }

        return nullptr;
    }
    /**
         * \brief Move Constructor
         */
    Node(Node&& ) = default;
    /**
         * \brief Copy Constructor
         */
    Node(const Node&) = default;
    /**
         * \brief Copy Assignment Operator
         */
    Node& operator=(const Node&) = default;
    /**
         * \brief Move Assingnment Operator
         */
    Node& operator=(Node&&) = default;

};

#endif // NODE_H
