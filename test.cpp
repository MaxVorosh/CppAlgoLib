#include <iostream>
#include <vector>
#include "segment_tree.h"

int my_max(int a, int b) {
    return std::max(a, b);
}

std::vector<int> vec_max(std::vector<int> a, std::vector<int> b) {
    return a.size() >= b.size() ? a : b;
}

int main() {
    const std::size_t size = 5;
    int values[size] = {1, 2, 3, 4, 5};
    std::function<int(int, int)> func = my_max;
    SegmentTree::SegmentTree<int> tree(values, size, func);
    std::cout << tree.get_segment(1, 3) << std::endl;
    int new_val = 10;
    tree.update(1, new_val);
    std::cout << tree.get_segment(1, 3) << std::endl;

    std::vector<int> vec_vals[size] = {{1}, {1, 2}, {1, 2, 3}, {1, 2, 3, 4}, {1, 2, 3, 4, 5}};
    std::function<std::vector<int>(std::vector<int>, std::vector<int>)> vec_func = vec_max;
    SegmentTree::SegmentTree<std::vector<int>> vec_tree(vec_vals, size, vec_func);
    std::vector<int> res = vec_tree.get_segment(1, 3);
    for (auto i: res) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    std::vector<int> new_vec = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    vec_tree.update(1, new_vec);
    res = vec_tree.get_segment(1, 3);
    for (auto i: res) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}