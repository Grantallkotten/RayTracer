#pragma once
#include <algorithm>
#include <glm/glm.hpp>
#include <iostream>
#include <thread>
#include <vector>

template <typename Data> struct KDNode {
  Data data;
  KDNode *left;
  KDNode *right;
  glm::vec3 minBounds; // Minimum bounding box corner
  glm::vec3 maxBounds; // Maximum bounding box corner

  KDNode(const Data &d) : data(d), left(nullptr), right(nullptr) {
    minBounds = maxBounds = d.position;
  }
};
template <typename Data> class KDTree {
  static_assert(std::is_member_pointer<decltype(&Data::position)>::value,
                "KDTree Data must implement a 'glm::vec3 position()' member.");

public:
  unsigned int size() { return m_size; }
  KDTree() : root(nullptr) {}

  // Function to insert data into the KD-Tree
  void insert(const Data &data) {
    insertRecursive(root, data, 0);
    m_size++;
  }

  // Function to build the KD-Tree from a vector of data
  void buildTree(std::vector<Data> &data) {
    root = buildTreeRecursiveParallel(data, 0, data.size(), 0);
  }

  std::vector<Data> rangeSearch(const glm::vec3 &center, double radius) {
    std::vector<Data> result;
    rangeSearchRecursive(root, center, radius, 0, result);
    return result;
  }

private:
  KDNode<Data> *root;
  unsigned int m_size = 0;

  // Helper function to insert data recursively
  void insertRecursive(KDNode<Data> *&node, const Data &data, int depth) {
    if (node == nullptr) {
      node = new KDNode<Data>(data);
    } else {
      node->minBounds = glm::min(node->minBounds, data.position);
      node->maxBounds = glm::max(node->maxBounds, data.position);

      int axis = depth % 3;
      if (data.position[axis] < node->data.position[axis]) {
        insertRecursive(node->left, data, depth + 1);
      } else {
        insertRecursive(node->right, data, depth + 1);
      }
    }
  }
  // Helper function to build the KD-Tree recursively in parallel
  KDNode<Data> *buildTreeRecursiveParallel(std::vector<Data> &data, int start,
                                           int end, int depth) {
    if (start >= end) {
      return nullptr;
    }

    int axis = depth % 3;
    int mid = (start + end) / 2;

    try {
      std::nth_element(data.begin() + start, data.begin() + mid,
                       data.begin() + end,
                       [axis](const Data &a, const Data &b) {
                         return a.position[axis] < b.position[axis];
                       });
    } catch (const std::exception &e) {
      std::cerr << "Exception during nth_element: " << e.what() << std::endl;
      throw; // Re-throw the exception to terminate the program or handle it as
             // needed.
    }

    KDNode<Data> *node = new KDNode<Data>(data[mid]);

    // std::thread leftThread([&]() {
    // try {
    // node->left = buildTreeRecursiveParallel(data, start, mid, depth + 1);
    //} catch (const std::exception &e) {
    // std::cerr << "Exception during left subtree construction: " << e.what()
    //<< std::endl;
    //// Handle the exception or re-throw as needed.
    //}
    //});

    node->left = buildTreeRecursiveParallel(data, start, mid, depth + 1);
    node->right = buildTreeRecursiveParallel(data, mid + 1, end, depth + 1);

    // leftThread.join(); // Wait for the left thread to finish
    m_size++;
    return node;
  }

  void rangeSearchRecursive(KDNode<Data> *node, const glm::vec3 &center,
                            double radius, int depth,
                            std::vector<Data> &result) {
    if (node == nullptr) {
      return;
    }

    // Check if the bounding box of this node is outside the search radius
    // if (isBoundingBoxOutsideSearchRadius(node, center, radius)) {
    //  return;
    //}

    // Calculate the squared distance between the point and the data in the node
    double distSq = 0.0;
    for (int i = 0; i < 3; i++) {
      double d = center[i] - node->data.position[i];
      distSq += d * d;
    }

    if (distSq <= radius * radius) {
      // Data in this node is within the radius
      result.push_back(node->data);
    }

    // Check which side of the current splitting plane the point is on
    int axis = depth % 3;
    if (center[axis] - radius <= node->data.position[axis]) {
      rangeSearchRecursive(node->left, center, radius, depth + 1, result);
    }
    if (center[axis] + radius >= node->data.position[axis]) {
      rangeSearchRecursive(node->right, center, radius, depth + 1, result);
    }
  }

  // Function to check if the bounding box of a node is entirely outside the
  // search radius
  bool isBoundingBoxOutsideSearchRadius(const KDNode<Data> *node,
                                        const glm::vec3 &center,
                                        double radius) {
    double sqDist = 0.0;

    // Calculate squared distance between the center and the bounding box
    for (int i = 0; i < 3; i++) {
      if (center[i] < node->minBounds[i]) {
        sqDist +=
            (node->minBounds[i] - center[i]) * (node->minBounds[i] - center[i]);
      } else if (center[i] > node->maxBounds[i]) {
        sqDist +=
            (center[i] - node->maxBounds[i]) * (center[i] - node->maxBounds[i]);
      }
    }

    return sqDist > radius * radius;
  }
};
