#include <data_structures/kdtree/kdtree.h>
#include "common/node.cpp"
#include "kdtree.cpp"

int main(){
    std::vector< std::vector<int> > data = {{1,2},{3,4},{5,6},{9,10}};
    std::vector<int> data1 = {7,8};
    KdTree<int> Tree;
    Tree.build({{1,2},{3,4},{5,6},{9,10}});
    Tree.insert({7,8});
    std::vector<int> mi;
    Tree.min(mi, 0);
    for(const auto& i : mi)
    {
        std::cout << i <<'\t';
    }
    Tree.erase({7,8});
    Tree.find({1,2});
    Tree.view();
}
