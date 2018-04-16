#include<data_structures/binarytree/binarytree.h>

int main()
{
    Binarytree<double> tree;
    std::vector<double> m1;
    std::vector<double> m2;
    tree.insert({6});
    tree.insert({2});
    tree.insert({9});
    tree.insert({1});
    //tree.build({{2}, {9}, {1}});
    tree.insert({8});
    tree.insert({15});
    tree.insert({13});
    tree.insert({11});
    tree.insert({18});
    tree.min(m1);
    tree.max(m2);
    tree.find({11});
    tree.erase({7.4});
    std::cout << m1.at(0) << '\n';
    std::cout << m2.at(0) << '\n';
    tree.view();
    return 0;
}
