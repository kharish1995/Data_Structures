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
    std::vector<T> value_;
    /**
         * \brief pointers to children nodes
         */
    std::vector<std::shared_ptr<Node<T> > > nodes_;

public:
    /**
         * \brief Set the values of the Node
         */
    virtual void setValue(std::vector<T>& value);
    /**
         * \brief Set the pointer to the Node
         */
    virtual void setNode(std::shared_ptr<Node<T> > , unsigned int);
    /**
         * \brief constructs node object with the value given value
         */
    Node(std::vector<T>& , unsigned int size = 2);
    /**
         * \brief constructs node object with the value given pointer to value
         */
    Node(std::vector<T>* , unsigned int size = 2);
    /**
         * \brief deletes Node object
         */
    virtual ~Node();
    /**
         * \brief get the value of a particular dimension
         */
    virtual T getValue(unsigned int) const;
    /**
         * \brief get the entire node value
         */
    virtual std::vector<T> getValues() const;
    /**
         * \brief get one of the children of the node
         */
    virtual std::shared_ptr<Node<T> > getNode(unsigned int) const;
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
