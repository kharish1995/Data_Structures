#include <data_structures/kdtree/kdtree.h>
#include "kdtree.cpp"

int main(){
    std::vector< std::vector<int> > data;
    std::vector<int> data1;
    KdTree<int> Tree(2);
    Tree.find(data1);
    Tree.build(data);
    std::vector<int> ma;
    std::vector<int> mi;
    Tree.max(ma,1);
    Tree.min(mi,1);
    Tree.erase(data1);
}

