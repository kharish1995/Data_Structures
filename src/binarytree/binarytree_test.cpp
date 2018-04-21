#include<data_structures/binarytree/binarytree.h>

int main()
{
    Binarytree<int> tree;
    int m1;
    int m2;
    tree.insert(1);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    //tree.build({{2}, {9}, {1}});
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    //tree.insert({18});
    tree.min(m1);
    tree.max(m2);
    tree.find(2);
    tree.erase(8);
    std::cout << m1 << '\n';
    std::cout << m2 << '\n';
    tree.view();
    return 0;
}
