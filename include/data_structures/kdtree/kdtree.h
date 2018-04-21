/** @file kdtree.h
 *  @brief KdTree Class
 *
 *  This contains the definitions and helper functions for KdTree class
 *
 *  @author Harish Karunakaran
 *  @author Shravan Murlidaran
 *  @bug No known bugs.
 */

#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <functional>
#include <data_structures/common/node.h>

template <typename T>
class KdTree
{
    /**
         * \brief Typedef for root node type
         */
    typedef std::shared_ptr<Node<std::vector<T> > > BasePtr;
    /**
         * \brief Root Node of the KdTree
         */
    BasePtr root_;
    /**
         * \brief splitting axis of the data
         */
    unsigned int cutDimension_;
    /**
         * \brief dimension of the input data
         */
    unsigned int dataDimension_ = 2;

protected:

    /** @brief Helper function to insert a node into the Kdtree - returns nullptr if it can't be inserted
     *  @param data Data to be inserted - const ref
     *  @param kd_node shared_ptr to the root node of kdtree
     *  @param cd unsigned int representing the cut dimension
     *  @return shared_ptr to the inserted node
     */
    BasePtr insertNode(const std::vector<T>& data,
                       BasePtr kd_node,
                       unsigned int cd)
    {

        if(kd_node == nullptr) kd_node = std::make_shared<Node<std::vector<T> > >(data, dataDimension_);

        else if(data == kd_node->getValues())
            return nullptr;

        else if(data.at(cd) < kd_node->getValue(cd))
            kd_node->setNode(insertNode(data, kd_node->getNode(0), (cd+1) % dataDimension_), 0);

        else
            kd_node->setNode(insertNode(data, kd_node->getNode(1), (cd+1) % dataDimension_), 1);

        return kd_node;
    }
    /** @brief Helper function to find a node in Kdtree - returns nullptr if it is not found
     *  @param data Data to be found - const ref
     *  @param kd_node shared_ptr to the root node of kdtree
     *  @param axis unsigned int representing the cut dimension
     *  @return axis shared_ptr to the found node
     */
    BasePtr findNode(const std::vector<T>& data,
                     BasePtr kd_node,
                     unsigned int axis) const
    {
        if (kd_node == nullptr)
            return nullptr;

        int new_axis = (axis + 1) % dataDimension_;

        if(data == kd_node->getValues())
            return kd_node;

        else if (data.at(axis) < kd_node->getValue(axis))
            kd_node = findNode(data, kd_node->getNode(0), new_axis);

        else
            kd_node = findNode(data, kd_node->getNode(1), new_axis);

        return kd_node;
    }
    /** @brief Helper function to delete a node in Kdtree - returns nullptr if it can't be deleted
     *  eg. if the node is not found in the tree, it returns a nullptr
     *  @param data Data to be deleted - const ref
     *  @param kd_node shared_ptr to the root node of kdtree
     *  @param axis unsigned int representing the cut dimension
     *  @return shared_ptr to the node replaced at the place of the deleted node
     */
    BasePtr deleteNode(const std::vector<T>& data,
                       BasePtr kd_node,
                       unsigned int axis)
    {
        if (kd_node == nullptr)
            return nullptr;

        unsigned int new_axis = (axis + 1) % dataDimension_;

        if(data == kd_node->getValues()){
            if(kd_node->getNode(1) != nullptr){
                auto min1 = minNode(kd_node->getNode(1), axis, new_axis)->getValues();
                kd_node->setValue(min1);
                kd_node->setNode(deleteNode(kd_node->getValues(), kd_node->getNode(1), new_axis), 1);
        }

            else if(kd_node->getNode(0) != nullptr){
                auto min0 = minNode(kd_node->getNode(0), axis, new_axis)->getValues();
                kd_node->setValue(min0);
                kd_node->setNode(deleteNode(kd_node->getValues(), kd_node->getNode(0), new_axis), 1);
        }
            else
                kd_node = nullptr;
        }
        else if (data.at(axis) < kd_node->getValue(axis))
            kd_node->setNode(deleteNode(data, kd_node->getNode(0), new_axis), 0);

        else
            kd_node->setNode(deleteNode(data, kd_node->getNode(1), new_axis), 1);

        return kd_node;
    }
    /** @brief Helper function to find the minimum node along a give axis in Kdtree - returns nullptr if it can't be found
     *  @param kd_node shared_ptr to the root node of kdtree
     *  @param axis unsigned int representing the axis to find the min node
     *  @param cd unsigned int representing the cut dimension
     *  @return shared_ptr to the found node
     */
    BasePtr minNode(const BasePtr kd_node,
                    unsigned int axis,
                    unsigned int cd) const
    {
        if (kd_node == nullptr)
            return nullptr;

        if (cd == axis)
        {
            if (kd_node->getNode(0) == nullptr)
                return kd_node;

            return minNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
        }

        else
            return minimum(minNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                           minNode(kd_node->getNode(1), axis, (cd + 1) % dataDimension_),
                           kd_node,
                           axis);
    }
    /** @brief Helper function to find the maximum node along a give axis in Kdtree - returns nullptr if it can't be found
     *  @param kd_node shared_ptr to the root node of kdtree
     *  @param axis unsigned int representing the axis to find the max node
     *  @param cd unsigned int representing the cut dimension
     *  @return shared_ptr to the found node
     */
    BasePtr maxNode(const BasePtr kd_node,
                    unsigned int axis,
                    unsigned int cd) const
    {
        if (kd_node == nullptr)
            return nullptr;

        if (cd == axis)
        {
            if (kd_node->getNode(0) == nullptr)
                return kd_node;

            return maxNode(kd_node->getNode(0), axis, (cd+1) % dataDimension_);
        }

        else
            return maximum(maxNode(kd_node->getNode(0), axis, (cd + 1) % dataDimension_),
                           maxNode(kd_node->getNode(1), axis, (cd + 1) % dataDimension_),
                           kd_node,
                           axis);
    }

    /** @brief Helper function to find the minimum node among three nodes along a give axis in Kdtree
     *  @param node1 Node 1 in the form of shared_ptr
     *  @param node2 Node 2 in the form of shared_ptr
     *  @param node3 Node 3 in the form of shared_ptr
     *  @param axis unsigned int representing the axis to find the minimum among the nodes
     *  @return shared_ptr to the minimum node
     */
    BasePtr minimum(const BasePtr node1,
                    const BasePtr node2,
                    const BasePtr node3,
                    unsigned int axis) const
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

    /** @brief Helper function to find the maximum node among three nodes along a give axis in Kdtree
     *  @param node1 Node 1 in the form of shared_ptr
     *  @param node2 Node 2 in the form of shared_ptr
     *  @param node3 Node 3 in the form of shared_ptr
     *  @param axis unsigned int representing the axis to find the maximum among the nodes
     *  @return shared_ptr to the maximum node
     */
    BasePtr maximum(const BasePtr node1,
                    const BasePtr node2,
                    const BasePtr node3,
                    unsigned int axis) const
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

    /** @brief Visualize the tree in a horizontal way
     *  @param node shared_ptr to the node to starting visualizing from
     *  @param space unsigned int representing the number of spaces after each node
     *  @return shared_ptr to the minimum node
     */
    void visualizeTree(const BasePtr node,
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
    /** @brief Default constructor
     *  set root node to nullptr and the cutDimension_ to zero
     */
    KdTree()
    {
        std::cout << "ctor - KdTree \n";
        root_ = nullptr;
        cutDimension_ = 0;
    }

    /** @brief Constructor which takes as input the cut dimension
     *  set root node to nullptr and the cutDimension_ to input
     *  @param cd unsigned int representing the starting cut dimension
     */
    KdTree(const unsigned int cd) : cutDimension_(cd)
    {
        std::cout << "ctor - KdTree \n";
        root_ = nullptr;
    }

    /** @brief Constructor which takes as input the cut dimension and the data
     *  set root node to data and the cutDimension_ to input
     *  @param data std::vector representing the root data
     *  @param cd unsigned int representing the starting cut dimension
     */
    KdTree(const std::vector<T>& data,
           unsigned int cd) : cutDimension_(cd),
                              root_(std::make_shared<Node<std::vector<T> > >(data, data.size()))
    {
        std::cout << "ctor - KdTree \n";
    }

    /** @brief Destructor for the Kdtree class
     */
    ~KdTree()
    {

    }

    /** @brief Public function to build the kdtree from a vector of vectors
     *  Takes one vector at a time and calls insert on them
     *  @param data std::vector of vectors representing all the data - Universal reference
     *  @return bool to represent whether the build was successful
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

    /** @brief Public function to insert data into the kdtree from a vector
     *  @param data std::vector representing the data - Universal reference
     *  @return bool to represent whether the insert was successful
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
            root_ = std::make_shared<Node<std::vector<T> > >(data, data.size());
            dataDimension_ = data.size();
            return true;
        }

        if(insertNode(data, root_, cutDimension_) == nullptr)
            return false;

        return true;
    }

    /** @brief Public function to find data in the kdtree
     *  @param data std::vector representing the data to be found - Universal reference
     *  @return bool to represent whether the find was successful
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

        if(findNode(data, root_, cutDimension_) == nullptr){
            std::cout << "Point not found" << '\n';
            return false;
        }

        return true;
    }

    /** @brief Public function to erase data from the kdtree
     *  @param data std::vector representing the data to be erased - Universal reference
     *  @return bool to represent whether the erase was successful
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

        else if(deleteNode(data, root_, cutDimension_) == nullptr){
            std::cout << "Point not found" << '\n';
            return false;
        }

        return true;
    }

    /** @brief Public function to find minium data along a particular axis in the kdtree
     *  @param minimum std::vector to store the minimum
     *  @param axis unsigned int representing the axis to find the minimum value
     *  @return void
     */
    void min(std::vector<T>& minimum,
             unsigned int axis) const
    {
        if(root_ == nullptr) return;
        minimum = (minNode(root_, axis, cutDimension_))->getValues();
    }

    /** @brief Public function to find maximum data along a particular axis in the kdtree
     *  @param maximum std::vector to store the maximum
     *  @param axis unsigned int representing the axis to find the maximum value
     *  @return void
     */
    void max(std::vector<T>& maximum,
             unsigned int axis) const
    {
        if(root_ == nullptr) return;
        maximum = (maxNode(root_, axis, cutDimension_))->getValues();
    }

    /** @brief Public function to view the data in the tree - starts from the root node
     *  @return void
     */
    void view() const
    {
        visualizeTree(root_, 0);
    }

    /** @brief Move Constructor
     */
    KdTree(KdTree&& ) noexcept = default;

    /** @brief Copy Constructor
     */
    KdTree(const KdTree& kdtree) : root_(kdtree.root_)
    {
        std::cout << "copy - KdTree \n";
    }

    /** @brief Copy Assignment Operator
     */
    KdTree& operator=(const KdTree& kdtree) noexcept
    {
        return *this = Kdtree(kdtree);
    }

    /** @brief Move Assignment Operator
     */
    KdTree& operator=(KdTree&&) noexcept = default;

};

#endif // KDTREE_H
