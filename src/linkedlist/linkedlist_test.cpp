#include <data_structures/linkedlist/linkedlist.h>
#include <algorithm>

int main()
{
    Linkedlist<int> ll;
    ll.insert(7);
    ll.insert(4);
    ll.insert(3);
    ll.insert(2);
    ll.erase(2);
    //ll.view();
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

