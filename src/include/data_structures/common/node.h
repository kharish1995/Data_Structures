#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

class Node
{
    struct concept_t
    {
        virtual ~concept_t() = default;
        virtual std::unique_ptr<concept_t> copy_() const = 0;
    };

    template <typename T>
    struct model final : concept_t
    {
        model(std::vector<T> x) : value_(std::move(x)) { }
        std::unique_ptr<concept_t> copy_() const override
        {
            return std::make_unique<model>(*this);
        }

        std::vector<T> value_;
    };

    /**
         * \brief stores the data in the node
         */
    std::unique_ptr<concept_t> self_;
    /**
         * \brief pointers to children nodes
         */
    std::vector<std::shared_ptr<Node> > nodes_;

public:
    /**
         * \brief Set the values of the Node
         */
    template<typename T>
    void setValue(std::vector<T> value)
    {
        self_ = std::make_unique<model<T> >(std::move(value));
    }
    /**
         * \brief Set the pointer to the Node
         */
    virtual void setNode(std::shared_ptr<Node> node, unsigned int i)
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
    template <typename T>
    Node(std::vector<T> value, unsigned int size) : self_(std::make_unique<model<T> >(std::move(value))), nodes_(size, nullptr)
    {
        std::cout << "ctor - Node \n";
        //value_ = value;
    }
    /**
         * \brief deletes Node object
         */
    ~Node();
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

    template <typename T>
    T getValue(unsigned int i) const
    {
        model<T>* derivedpointer = dynamic_cast<model<T>* >(self_);
        try{
            return derivedpointer->value_.at(i);
        }
          catch (const std::out_of_range& e){
            std::cerr << "Index Out of bounds for Node " << e.what() << '\n';
        }

        return false;
    }

    template <typename T>
    std::vector<T> getValues() const
    {
        model<T>* derivedpointer = dynamic_cast<model<T>* >(self_);
        return  derivedpointer->value_;
    }

    /**
         * \brief Move Constructor
         */
    Node(Node&& ) = default;
    /**
         * \brief Copy Constructor
         */
    Node(const Node& x) : self_(x.self_->copy_()) { }
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
