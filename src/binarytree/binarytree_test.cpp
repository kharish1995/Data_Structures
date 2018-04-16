#include<data_structures/binarytree/binarytree.h>

int main()
{
    Binarytree<double> tree;
    tree.insert({7});
    tree.insert({8});
    tree.insert({6});
    tree.insert({7.5});
    tree.insert({10});
    tree.view();
    return 0;
}
