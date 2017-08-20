#include<data_structures/kdtree/kdtree.h>
#include "kdtree.cpp"

int main(){
std::vector< std::vector<int> > data;
KdTree<int> Tree(2);
Tree.buildTree(data);
std::vector<int> ma;
std::vector<int> mi;
Tree.findMax(ma,1);
Tree.findMin(mi,1);
}

