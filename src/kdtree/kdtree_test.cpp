#include <data_structures/kdtree/kdtree.h>
#include "kdtree.cpp"

int main(){
    std::vector< std::vector<int> > data;
    std::vector<int> data1;
    KdTree<int> Tree(2);
    Tree.buildTree(data);
    std::vector<int> ma;
    std::vector<int> mi;
    Tree.find_max(ma,1);
    Tree.find_min(mi,1);
    Tree.delete_node(data1);
}

