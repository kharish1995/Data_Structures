/** @file node.h
 *  @brief Node Class
 *
 *  This contains the helper functions for Node class
 *  and a template specialization for std::vector
 *
 *  @author Harish Karunakaran
 *  @author Shravan Murlidaran
 *  @bug No known bugs.
 */

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
    /** @brief Sets the value of the current node
     *  @param value Universal reference of class type
     *  @return Void.
     */
    template <
        class UR = T,
        class TypeMustBeT = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, T>::value>
    >
    void setValue(UR&& value)
    {
        value_ = value;
    }

    /** @brief Sets the node at particular position
     *  eg. nodes_.at(0) for a binary tree sets the left node to the desired pointer
     *  @param node shared_ptr to the node to be set
     *  @param i unsigned integer representing the index of the vector to set the node
     *  @return Void.
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

    /** @brief Constructs the node when given a value - const ref
     *  @param value value of the node
     *  @param size unsigned integer representing the number of children nodes to the current node
     *  @return Void.
     */

    Node(const T& value, unsigned int size = 2) : nodes_(size, nullptr)
    {
        value_ = value;
    }

    /** @brief Constructs the node when given a value - input is via pointer
     *  @param value pointer to value in the node
     *  @param size unsigned integer representing the number of children nodes to the current node
     *  @return Void.
     */
    Node(const T* value, unsigned int size = 2): nodes_(size, nullptr)
    {
        value_ = *value;
    }
    /** @brief Destructor
     * Destroys the node object
     *  @return Void.
     */
    ~Node()
    {

    }
    /** @brief Returns the value of the current node
     *  @return Value at the node
     */
    T getValue() const
    {
        return value_;
    }
    /** @brief Returns a shared_ptr to one of the child node of the current node
     *  @param i unsigned integer representing which children should be returned
     *  @return shared_ptr to the child node
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
    /** @brief Move Constructor set to default
     */
    Node(Node&& ) = default;

    /** @brief Copy Constructor set to default
     */
    Node(const Node&) = default;

    /** @brief Copy Assignment Operator set to default
     */
    Node& operator=(const Node&) = default;


    /** @brief Move Assignment Operator set to default
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
    /** @brief Sets the value of the current node
     *  @param value Universal reference of class type
     *  @return Void.
     */
    template <
        class UR = std::vector<U>,
        class TypeMustBeStdVector = std::enable_if_t<std::is_same<std::remove_reference_t<UR>, std::vector<U> >::value>
    >
    void setValue(const UR&& value)
    {
        value_ = value;
    }
    /** @brief Sets the node at particular position
     *  eg. nodes_.at(0) for a binary tree sets the left node to the desired pointer
     *  @param node shared_ptr to the node to be set
     *  @param i unsigned integer representing the index of the vector to set the node
     *  @return Void.
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
    /** @brief Constructs the node when given a value - const ref
     *  @param value value of the node
     *  @param size unsigned integer representing the number of children nodes to the current node
     *  @return Void.
     */
    Node(const std::vector<U>& value, unsigned int size = 2) : nodes_(size, nullptr)
    {
        value_ = value;
    }
    /** @brief Constructs the node when given a value - input is via pointer
     *  @param value pointer to value in the node
     *  @param size unsigned integer representing the number of children nodes to the current node
     *  @return Void.
     */
    Node(const std::vector<U>* value, unsigned int size = 2): nodes_(size, nullptr)
    {
        value_ = *value;
    }
    /** @brief Destructor
     * Destroys the node object
     *  @return Void.
     */
    ~Node()
    {

    }

    /** @brief Returns the value along a particular dimension of the current node
     *  @param i unsigned integer representing the which dimension to obtain the data from
     *  @return value along a particular dimension at the node
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

    /** @brief Returns the value of the current node
     *  @return value at the node
     */
    std::vector<U> getValues() const
    {
        return value_;
    }
    /** @brief Returns a shared_ptr to one of the child node of the current node
     *  @param i unsigned integer representing which children should be returned
     *  @return shared_ptr to the child node
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
    /** @brief Move Constructor set to default
     */
    Node(Node&& ) = default;

    /** @brief Copy Constructor set to default
     */
    Node(const Node&) = default;

    /** @brief Copy Assignment Operator set to default
     */
    Node& operator=(const Node&) = default;


    /** @brief Move Assignment Operator set to default
     */
    Node& operator=(Node&&) = default;

};

#endif // NODE_H
