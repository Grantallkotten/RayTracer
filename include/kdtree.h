#include <iostream>
#include <vector>
#include <algorithm>
#include "glm/glm.hpp"

template <class Data>
struct KDNode {
    Data data;
    KDNode* left;
    KDNode* right;

    KDNode(const Data& d) : data(d), left(nullptr), right(nullptr) {}
};

template <class Data>
class KDTree {
    static_assert(
        std::is_member_function_pointer<decltype(&Data::pos)>::value,
        "KDTree Data must implement a 'glm::dvec3 pos()' member."
        );

public:
    KDTree() : root(nullptr) {}

    // Function to insert data into the KD-Tree
    void insert(const Data& data) {
        insertRecursive(root, data, 0);
    }

    // Function to build the KD-Tree from a vector of data
    void buildTree(std::vector<Data>& data) {
        root = buildTreeRecursiveParallel(data, 0, data.size(), 0);
    }

private:
    KDNode<Data>* root;

    // Helper function to insert data recursively
    void insertRecursive(KDNode<Data>*& node, const Data& data, int depth) {
        if (node == nullptr) {
            node = new KDNode<Data>(data);
        }
        else if (data.pos(depth % 3) < node->data.pos(depth % 3)) {
            insertRecursive(node->left, data, depth + 1);
        }
        else {
            insertRecursive(node->right, data, depth + 1);
        }
    }

    // Helper function to build the KD-Tree recursively in parallel
    KDNode<Data>* buildTreeRecursiveParallel(std::vector<Data>& data, int start, int end, int depth) {
        if (start >= end) {
            return nullptr;
        }

        int axis = depth % 3;
        int mid = (start + end) / 2;

        std::nth_element(data.begin() + start, data.begin() + mid, data.begin() + end,
            [axis](const Data& a, const Data& b) {
                return a.pos(axis) < b.pos(axis);
            });

        KDNode<Data>* node = new KDNode<Data>(data[mid);

        // Parallelize left and right subtree construction
        std::thread leftThread([&]() {
            node->left = buildTreeRecursiveParallel(data, start, mid, depth + 1);
            });

        node->right = buildTreeRecursiveParallel(data, mid + 1, end, depth + 1);

        leftThread.join(); // Wait for the left thread to finish

        return node;
    }
};