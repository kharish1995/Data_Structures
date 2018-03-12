#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

template <typename T>
class Node
{
    std::vector<T> value_;
    /**
         * \brief pointers to children nodes
         */
    std::vector<std::shared_ptr<Node> > nodes_;

public:
    /**
         * \brief Set the values of the Node
         */
    void setValue(std::vector<T> value)
    {
        value_ = value;
    }
    /**
         * \brief Set the pointer to the Node
         */
    void setNode(std::shared_ptr<Node> node, unsigned int i)
    {
        if (i <= nodes_.size())
        {
            nodes_.at(i) = node;
            return;
        }
        std::cerr << "Index out of bounds for the node" << '\n';
    }
    /**
         * \brief constructs node object with the value given value
         */
    Node(std::vector<T> value, unsigned int size) : nodes_(size, nullptr)
    {
        std::cout << "ctor - Node \n";
        value_ = value;
    }
    /**
         * \brief deletes Node object
         */
    ~Node() { }
    /**
         * \brief get one of the children of the node
         */
    std::shared_ptr<Node> getNode(unsigned int i) const
    {
        try{
            return nodes_.at(i);
        }
          catch (const std::out_of_range& e){
            std::cerr << "Index Out of bounds for Node " << e.what() << '\n';
        }

        return nullptr;
    }

    T getValue(unsigned int i) const
    {
        try{
            return value_.at(i);
        }
          catch (const std::out_of_range& e){
            std::cerr << "Index Out of bounds for Node " << e.what() << '\n';
        }

        return false;
    }

    std::vector<T> getValues() const
    {
        return value_;
    }

    /**
         * \brief Move Constructor
         */
    Node(Node&& ) = default;
    /**
         * \brief Copy Constructor
         */
    Node(const Node& x) = default;
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
