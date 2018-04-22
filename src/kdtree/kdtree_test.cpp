#include <data_structures/kdtree/kdtree.h>
#include <chrono>

using namespace std::chrono;
int main()
{
    std::vector< std::vector<int> > data = {{1,2},{3,4},{5,6},{9,10}};
    std::vector<int> data1 = {7,8};
    KdTree<int> Tree;

    auto start = high_resolution_clock::now();
        Tree.build({{1,2},{3,4},{5,6},{9,10}});

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time " << duration.count() << std::endl;
            Tree.insert({7,8});
    std::vector<int> mi;
    Tree.min(mi, 0);
    for(const auto& i : mi)
    {
        std::cout << i <<'\t';
    }
    Tree.find({4,5});
    Tree.view();
}
