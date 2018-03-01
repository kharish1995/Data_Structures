#include "common/node.cpp"
#include <data_structures/kdtree/kdtree.h>
#include <algorithm>

//KdTree<int> func()
//{
//    std::vector< std::vector<int> > data = {{1,2},{3,4},{5,6},{9,10}};
//    //KdTree<int> result{};
//    //result.build(data);
//    return KdTree<int>{};
//}

int main()
{
    std::vector< std::vector<int> > data = {{1,2},{3,4},{5,6},{9,10}};
    KdTree<int> b;
    KdTree<int> c;
    KdTree<int> d;
    KdTree<int> e;
    std::vector<KdTree<int> > x;
    x.reserve(5);
    x.emplace_back(KdTree<int>{});
    //x.emplace_back(KdTree<float>{});
    x.emplace_back(KdTree<int>{});
    x.emplace_back(KdTree<int>{});
    //std::reverse(x.begin(), x.end());
//    //std::reverse(x.begin(),x.end());
    //x.view();
//    std::vector< std::vector<int> > data = {{1,2},{3,4},{5,6},{9,10}};
//    std::vector<int> data1 = {7,8};
//    KdTree<int> Tree;
//    Tree.build({{1,2},{3,4},{5,6},{9,10}});
//    Tree.insert({7,8});
//    std::vector<int> mi;
//    Tree.min(mi, 0);
//    for(const auto& i : mi)
//    {
//        std::cout << i <<'\t';
//    }
//    Tree.erase({7,8});
//    Tree.find({3,4});
//    Tree.view();
}
